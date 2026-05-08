#!/bin/bash
# Comprehensive minishell tester (skipping export/unset)
# The tty check has been temporarily disabled for piped testing.

MINISHELL="./minishell"
SUPP="readline.supp"
PASS=0
FAIL=0
TOTAL=0
ERRORS=""

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

# Strip minishell prompt lines + echoed-back input from output.
# When piped, readline echoes "minishell> <input>" before the output.
# We remove all lines starting with "minishell> " and "exit" lines.
strip_output() {
    grep -v '^minishell>' | grep -v '^exit$'
}

run_test() {
    local test_name="$1"
    local input="$2"
    local expected_stdout="$3"
    local expected_status="$4"
    local compare_bash="$5"
    
    TOTAL=$((TOTAL + 1))
    
    mini_raw=$(printf '%s\n' "$input" | $MINISHELL 2>/dev/null)
    mini_status=$?
    mini_out=$(echo "$mini_raw" | strip_output)
    # Remove trailing empty lines
    mini_out=$(echo "$mini_out" | sed '/^[[:space:]]*$/d')
    
    local failed=0
    local reason=""
    
    if [ "$compare_bash" = "bash" ]; then
        bash_out=$(printf '%s\n' "$input" | bash 2>/dev/null)
        bash_status=$?
        bash_out=$(echo "$bash_out" | sed '/^[[:space:]]*$/d')
        if [ "$mini_out" != "$bash_out" ]; then
            failed=1
            reason="STDOUT differs from bash. Bash: '$(echo "$bash_out" | head -2)', Mini: '$(echo "$mini_out" | head -2)'"
        fi
        if [ -n "$expected_status" ] && [ "$mini_status" != "$expected_status" ]; then
            failed=1
            reason="${reason:+$reason | }STATUS: expected $expected_status, got $mini_status (bash=$bash_status)"
        fi
    else
        if [ -n "$expected_stdout" ]; then
            if [ "$mini_out" != "$expected_stdout" ]; then
                failed=1
                reason="STDOUT: expected '$expected_stdout', got '$mini_out'"
            fi
        fi
        if [ -n "$expected_status" ]; then
            if [ "$mini_status" != "$expected_status" ]; then
                failed=1
                reason="${reason:+$reason | }STATUS: expected $expected_status, got $mini_status"
            fi
        fi
    fi
    
    if [ $failed -eq 0 ]; then
        PASS=$((PASS + 1))
        echo -e "  ${GREEN}✓${NC} $test_name"
    else
        FAIL=$((FAIL + 1))
        echo -e "  ${RED}✗${NC} $test_name"
        echo -e "    ${YELLOW}→ $reason${NC}"
        ERRORS="${ERRORS}\n  ✗ $test_name: $reason"
    fi
}

run_valgrind_test() {
    local test_name="$1"
    local input="$2"
    
    TOTAL=$((TOTAL + 1))
    
    printf '%s\n' "$input" | valgrind --suppressions=$SUPP --leak-check=full --show-leak-kinds=all --track-fds=yes --log-file=valgrind_out.txt $MINISHELL > /dev/null 2>/dev/null
    
    local failed=0
    local reason=""
    
    # Check definitely lost
    def_lost=$(grep "definitely lost:" valgrind_out.txt | head -1)
    if echo "$def_lost" | grep -qvE "0 bytes in 0 blocks"; then
        failed=1
        reason="LEAK: $(echo $def_lost | sed 's/.*==//')"
    fi
    
    # Check invalid memory access
    inv_count=$(grep -c "Invalid read\|Invalid write\|Invalid free\|Use of uninitialised" valgrind_out.txt 2>/dev/null || echo 0)
    if [ "$inv_count" -gt 0 ]; then
        inv_detail=$(grep -m1 "Invalid read\|Invalid write\|Invalid free\|Use of uninitialised" valgrind_out.txt)
        failed=1
        reason="${reason:+$reason | }MEMORY ERRORS ($inv_count): $inv_detail"
    fi

    # Check leaked FDs (not inherited)
    fd_leaks=$(grep "Open file descriptor" valgrind_out.txt | grep -v "inherited from parent" | wc -l)
    if [ "$fd_leaks" -gt 0 ]; then
        fd_detail=$(grep -B0 -A2 "Open file descriptor" valgrind_out.txt | grep -v "inherited from parent" | head -6)
        failed=1
        reason="${reason:+$reason | }FD LEAKS ($fd_leaks): $(echo $fd_detail)"
    fi
    
    if [ $failed -eq 0 ]; then
        PASS=$((PASS + 1))
        echo -e "  ${GREEN}✓${NC} [VALGRIND] $test_name"
    else
        FAIL=$((FAIL + 1))
        echo -e "  ${RED}✗${NC} [VALGRIND] $test_name"
        echo -e "    ${YELLOW}→ $reason${NC}"
        ERRORS="${ERRORS}\n  ✗ [VALGRIND] $test_name: $reason"
    fi
}

rm -f /tmp/mini_test_* /tmp/mini_valgrind_* /tmp/mt[0-9]* valgrind_out.txt

echo -e "\n${CYAN}${BOLD}═══════════════════════════════════════════════${NC}"
echo -e "${CYAN}${BOLD}       MINISHELL COMPREHENSIVE TEST SUITE       ${NC}"
echo -e "${CYAN}${BOLD}═══════════════════════════════════════════════${NC}\n"

# ═══════════════════════════════════════
echo -e "${CYAN}━━ ECHO TESTS ━━${NC}"
run_test "echo hello" "echo hello" "hello" ""
run_test "echo multi words" "echo hello world" "hello world" ""
run_test "echo empty" "echo" "" "" "bash"
run_test "echo -n hello" "echo -n hello" "" "" "bash"
run_test "echo -n -n -n hello" "echo -n -n -n hello" "" "" "bash"
run_test "echo -nnnnn hello" "echo -nnnnn hello" "" "" "bash"
run_test "echo -n (no text)" "echo -n" "" "" "bash"
run_test "echo double quoted" 'echo "hello world"' "hello world" ""
run_test "echo single quoted" "echo 'hello world'" "hello world" ""
run_test "echo mixed quotes" "echo \"hello\"'world'" "helloworld" ""
run_test "echo empty dquotes" 'echo ""' "" "" "bash"
run_test "echo empty squotes" "echo ''" "" "" "bash"
run_test "echo spaces collapsed" "echo hello    world" "hello world" ""

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ PWD TESTS ━━${NC}"
run_test "pwd basic" "pwd" "$(pwd)" ""

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ CD TESTS ━━${NC}"
run_test "cd no arg (HOME)" "cd
pwd" "$HOME" ""
run_test "cd / then pwd" "cd /
pwd" "/" ""
run_test "cd /tmp then pwd" "cd /tmp
pwd" "/tmp" ""
run_test "cd .. from /tmp" "cd /tmp
cd ..
pwd" "/" ""
run_test "cd nonexistent (stderr)" "cd /nonexistent_dir 2>&1 | grep -c 'No such file'" "" "" ""
run_test "cd too many args" "cd a b 2>&1 | grep -c 'too many'" "" "" ""

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ EXIT STATUS (\$?) TESTS ━━${NC}"
run_test "\$? = 0 after echo" "echo hello
echo \$?" "" "" "bash"
run_test "\$? = 1 after /bin/false" "/bin/false
echo \$?" "" "" "bash"
run_test "\$? = 0 after /bin/true" "/bin/true
echo \$?" "" "" "bash"
run_test "\$? = 127 after bad cmd" "nonexistent_cmd_xyz 2>/dev/null
echo \$?" "" "" "bash"
run_test "\$? = 1 after cd fail" "cd /no_such_dir 2>/dev/null
echo \$?" "" "" "bash"

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ VARIABLE EXPANSION ━━${NC}"
run_test "expand \$HOME" 'echo $HOME' "$HOME" ""
run_test "expand \$USER" 'echo $USER' "$USER" ""
run_test "expand \$PATH" 'echo $PATH' "" "" "bash"
run_test "undefined var is empty" 'echo $UNDEFINED_VAR_XYZ' "" ""
run_test "\$? = 0" 'echo $?' "0" ""
run_test "dollar at end" 'echo hello$' "" "" "bash"
run_test "\$USER in dquotes" 'echo "$USER"' "$USER" ""
run_test "\$USER in squotes (literal)" "echo '\$USER'" '$USER' ""
run_test "text + \$USER + text" 'echo "hello $USER world"' "hello $USER world" ""
run_test "adjacent vars" 'echo $USER$HOME' "${USER}${HOME}" ""

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ PIPE TESTS ━━${NC}"
run_test "echo | cat" "echo hello | cat" "hello" ""
run_test "echo | grep" "echo hello world | grep hello" "hello world" ""
run_test "echo | wc -l" "echo hello | wc -l" "" "" "bash"
run_test "4-stage pipe" "echo hello | cat | cat | cat" "hello" ""
run_test "ls | head -1" "ls | head -1" "" "" "bash"
run_test "cat file | head" "cat /etc/passwd | head -3" "" "" "bash"
run_test "echo | wc -c" "echo hello | wc -c" "" "" "bash"
run_test "echo | tr | rev" "echo abc | tr a-z A-Z | rev" "CBA" ""
run_test "pipe status (last cmd)" "echo hello | /bin/false
echo \$?" "" "" "bash"
run_test "false | echo hi" "/bin/false | echo hi
echo \$?" "" "" "bash"

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ OUTPUT REDIRECTION ━━${NC}"
run_test "echo > file" "echo hello > /tmp/mini_test_o1
cat /tmp/mini_test_o1" "hello" ""
run_test "echo >> file (append)" "echo line1 > /tmp/mini_test_o2
echo line2 >> /tmp/mini_test_o2
cat /tmp/mini_test_o2" "" "" "bash"
run_test "overwrite file" "echo first > /tmp/mini_test_o3
echo second > /tmp/mini_test_o3
cat /tmp/mini_test_o3" "second" ""
run_test "multiple > (last wins)" "echo aaa > /tmp/mini_test_o4a > /tmp/mini_test_o4b
cat /tmp/mini_test_o4b" "aaa" ""

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ INPUT REDIRECTION ━━${NC}"
echo "test content" > /tmp/mini_test_i1
run_test "cat < file" "cat < /tmp/mini_test_i1" "test content" ""
printf "line1\nline2\nline3\n" > /tmp/mini_test_i2
run_test "cat < multi-line" "cat < /tmp/mini_test_i2" "" "" "bash"
run_test "cat < nonexistent" "cat < /tmp/nonexistent_xyz 2>/dev/null
echo \$?" "" "" "bash"

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ COMBINED REDIRECTIONS ━━${NC}"
echo "combined input" > /tmp/mini_test_c1
run_test "cat < in > out" "cat < /tmp/mini_test_c1 > /tmp/mini_test_c1_out
cat /tmp/mini_test_c1_out" "combined input" ""
run_test "echo > file; cat | wc" "echo hello world > /tmp/mini_test_c2
cat /tmp/mini_test_c2 | wc -w" "" "" "bash"

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ HEREDOC TESTS ━━${NC}"
run_test "heredoc basic" "$(printf 'cat << EOF\nhello\nEOF')" "hello" ""
run_test "heredoc multiline" "$(printf 'cat << END\nline1\nline2\nline3\nEND')" "" "" "bash"
run_test "heredoc with \$USER" "$(printf 'cat << EOF\n$USER\nEOF')" "$USER" ""

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ EXIT BUILTIN ━━${NC}"
run_test "exit -> 0" "exit" "" "0"
run_test "exit 42 -> 42" "exit 42" "" "42"
run_test "exit 0 -> 0" "exit 0" "" "0"
run_test "exit 255 -> 255" "exit 255" "" "255"
run_test "exit 256 -> 0 (mod)" "exit 256" "" "0"
run_test "exit -1 -> 255" "exit -1" "" "255"
run_test "exit abc -> 2" "exit abc 2>/dev/null" "" "2"
run_test "exit too many args (no exit)" "exit 1 2 3
echo \$?" "" "" ""

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ EDGE CASES ━━${NC}"
run_test "empty input" "" "" "" "bash"
run_test "only whitespace" "   " "" "" "bash"
run_test "/bin/echo hello" "/bin/echo hello" "hello" ""
run_test "nonexistent cmd status" "totally_fake_cmd 2>/dev/null
echo \$?" "" "" "bash"
# Semicolons are NOT required in minishell

# ═══════════════════════════════════════
echo -e "\n${CYAN}━━ ENV BUILTIN ━━${NC}"
run_test "env | wc -l" "env | wc -l" "" "" "bash"
run_test "env | grep PATH" "env | grep ^PATH= | wc -l" "" "" "bash"
run_test "env | grep HOME" "env | grep ^HOME= | wc -l" "" "" "bash"

# ═══════════════════════════════════════════════════
echo -e "\n${CYAN}${BOLD}═══════════════════════════════════════════${NC}"
echo -e "${CYAN}${BOLD}       VALGRIND MEMORY & FD TESTS           ${NC}"
echo -e "${CYAN}${BOLD}═══════════════════════════════════════════${NC}\n"

echo -e "${CYAN}━━ Memory Leak Tests ━━${NC}"
run_valgrind_test "echo hello" "echo hello"
run_valgrind_test "echo \$HOME" 'echo $HOME'
run_valgrind_test "pwd" "pwd"
run_valgrind_test "cd /tmp + pwd" "cd /tmp
pwd"
run_valgrind_test "cd (home)" "cd"
run_valgrind_test "cd nonexistent" "cd /no_such_dir"
run_valgrind_test "simple pipe" "echo hello | cat"
run_valgrind_test "triple pipe" "echo hi | cat | cat"
run_valgrind_test "echo > file" "echo test > /tmp/mini_valgrind1"
run_valgrind_test "cat < file" "echo data > /tmp/mini_valgrind_in
cat < /tmp/mini_valgrind_in"
run_valgrind_test "echo >> file" "echo a >> /tmp/mini_valgrind2
echo b >> /tmp/mini_valgrind2"
run_valgrind_test "cat < in > out" "echo x > /tmp/mini_valgrind_cin
cat < /tmp/mini_valgrind_cin > /tmp/mini_valgrind_cout"
run_valgrind_test "pipe + redir" "echo hello | cat > /tmp/mini_valgrind3"
run_valgrind_test "nonexistent cmd" "fake_command"
run_valgrind_test "multi echo" "echo a
echo b
echo c"
run_valgrind_test "\$? expansion" 'echo $?'
run_valgrind_test "empty quotes" 'echo ""'
run_valgrind_test "single quotes" "echo 'hello'"
run_valgrind_test "/bin/false + \$?" "/bin/false
echo \$?"
run_valgrind_test "env | head" "env | head -1"
run_valgrind_test "heredoc basic" "$(printf 'cat << EOF\nhello\nEOF')"
run_valgrind_test "echo with vars" 'echo "$HOME" $USER'
run_valgrind_test "pipe + expansion" 'echo $HOME | cat'

echo -e "\n${CYAN}━━ FD Leak Stress Tests ━━${NC}"
run_valgrind_test "5-stage pipe" "echo a | cat | cat | cat | cat"
run_valgrind_test "5 redirections" "echo a > /tmp/mt1
echo b > /tmp/mt2
echo c > /tmp/mt3
echo d > /tmp/mt4
echo e > /tmp/mt5"
run_valgrind_test "pipe + redir x2" "ls | cat > /tmp/mt6
ls | cat > /tmp/mt7"
run_valgrind_test "in + out redir" "echo hello > /tmp/mt8
cat < /tmp/mt8 > /tmp/mt9"
run_valgrind_test "heredoc + pipe" "$(printf 'cat << EOF | cat\nhello\nEOF')"

# Cleanup temp files
rm -f /tmp/mini_test_* /tmp/mini_valgrind_* /tmp/mt[0-9]* valgrind_out.txt

# ═══════════════════════════════════════
echo -e "\n${CYAN}${BOLD}═══════════════════════════════════════════${NC}"
echo -e "${CYAN}${BOLD}              FINAL RESULTS                ${NC}"
echo -e "${CYAN}${BOLD}═══════════════════════════════════════════${NC}"
echo -e "  ${BOLD}Total:  $TOTAL${NC}"
echo -e "  ${GREEN}${BOLD}Passed: $PASS${NC}"
echo -e "  ${RED}${BOLD}Failed: $FAIL${NC}"
if [ $FAIL -gt 0 ]; then
    echo -e "\n${RED}${BOLD}── Failed Tests Summary ──${NC}"
    echo -e "$ERRORS"
fi
echo ""

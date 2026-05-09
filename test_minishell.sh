#!/bin/bash
# Comprehensive minishell tester v6 — enhanced with extra edge cases
# Covers: echo, cd, pwd, pipes, redirections, heredoc, exit, expansion, env, syntax, signals, valgrind

MS="./minishell"
SUPP="readline.supp"
PASS=0; FAIL=0; TOTAL=0; ERRORS=""
G='\033[0;32m'; R='\033[0;31m'; Y='\033[0;33m'; C='\033[0;36m'; B='\033[1m'; N='\033[0m'

# Strip prompt lines AND heredoc "> " prefix from piped output
strip() {
    grep -v '^minishell>' | grep -v '^exit$' | grep -v '^> ' | sed '/^[[:space:]]*$/d'
}

# Run minishell and capture both output and exit status via temp file
run_ms() {
    local input="$1"
    local tmpf=$(mktemp /tmp/ms_run_XXXXXX)
    printf '%s\n' "$input" | $MS > "$tmpf" 2>/dev/null
    MS_STATUS=$?
    MS_OUTPUT=$(cat "$tmpf" | strip)
    rm -f "$tmpf"
}

test_vs_bash() {
    local name="$1" input="$2"
    TOTAL=$((TOTAL + 1))
    run_ms "$input"
    local b_out b_st
    b_out=$(printf '%s\n' "$input" | bash 2>/dev/null | sed '/^[[:space:]]*$/d')
    b_st=$?
    local fail=0 reason=""
    [ "$MS_OUTPUT" != "$b_out" ] && { fail=1; reason="OUT: bash='$(echo "$b_out"|head -2)' mini='$(echo "$MS_OUTPUT"|head -2)'"; }
    [ "$MS_STATUS" != "$b_st" ] && { fail=1; reason="${reason:+$reason | }STATUS: bash=$b_st mini=$MS_STATUS"; }
    if [ $fail -eq 0 ]; then PASS=$((PASS+1)); echo -e "  ${G}✓${N} $name"
    else FAIL=$((FAIL+1)); echo -e "  ${R}✗${N} $name"; echo -e "    ${Y}→ $reason${N}"; ERRORS="$ERRORS\n  ✗ $name: $reason"; fi
}

test_exact() {
    local name="$1" input="$2" exp_out="$3" exp_st="$4"
    TOTAL=$((TOTAL + 1))
    run_ms "$input"
    local fail=0 reason=""
    [ -n "$exp_out" ] && [ "$MS_OUTPUT" != "$exp_out" ] && { fail=1; reason="OUT: exp='$(echo "$exp_out"|head -2)' got='$(echo "$MS_OUTPUT"|head -2)'"; }
    [ -n "$exp_st" ] && [ "$MS_STATUS" != "$exp_st" ] && { fail=1; reason="${reason:+$reason | }STATUS: exp=$exp_st got=$MS_STATUS"; }
    if [ $fail -eq 0 ]; then PASS=$((PASS+1)); echo -e "  ${G}✓${N} $name"
    else FAIL=$((FAIL+1)); echo -e "  ${R}✗${N} $name"; echo -e "    ${Y}→ $reason${N}"; ERRORS="$ERRORS\n  ✗ $name: $reason"; fi
}

# Special test for echo -n: strip trailing prompt that merges with output
test_echo_n() {
    local name="$1" input="$2" exp_out="$3"
    TOTAL=$((TOTAL + 1))
    local tmpf=$(mktemp /tmp/ms_run_XXXXXX)
    printf '%s\n' "$input" | $MS > "$tmpf" 2>/dev/null
    MS_STATUS=$?
    # For echo -n, the output has no newline, so the next prompt merges.
    # Raw output looks like: "minishell> echo -n hello\nhellominishell> \n"
    # We need to strip "minishell> " lines AND remove trailing "minishell> " from merged line
    MS_OUTPUT=$(cat "$tmpf" | grep -v '^minishell>' | sed 's/minishell> $//' | sed '/^[[:space:]]*$/d')
    rm -f "$tmpf"
    local fail=0 reason=""
    [ "$MS_OUTPUT" != "$exp_out" ] && { fail=1; reason="OUT: exp='$exp_out' got='$MS_OUTPUT'"; }
    if [ $fail -eq 0 ]; then PASS=$((PASS+1)); echo -e "  ${G}✓${N} $name"
    else FAIL=$((FAIL+1)); echo -e "  ${R}✗${N} $name"; echo -e "    ${Y}→ $reason${N}"; ERRORS="$ERRORS\n  ✗ $name: $reason"; fi
}

run_valgrind() {
    local name="$1" input="$2"
    TOTAL=$((TOTAL + 1))
    printf '%s\n' "$input" | valgrind --suppressions=$SUPP --leak-check=full --show-leak-kinds=all --track-fds=yes --log-file=vg.txt $MS >/dev/null 2>/dev/null
    local fail=0 reason=""
    local dl=$(grep "definitely lost:" vg.txt | head -1)
    echo "$dl" | grep -qvE "0 bytes in 0 blocks" && { fail=1; reason="LEAK: $(echo $dl|sed 's/.*==//')"; }
    local ic=$(grep -c "Invalid read\|Invalid write\|Invalid free\|Use of uninitialised" vg.txt 2>/dev/null || echo 0)
    [ "$ic" -gt 0 ] 2>/dev/null && { fail=1; reason="${reason:+$reason | }MEM_ERR($ic)"; }
    local fl=$(grep "Open file descriptor" vg.txt | grep -v "inherited from parent" | wc -l)
    [ "$fl" -gt 0 ] && { fail=1; reason="${reason:+$reason | }FD_LEAK($fl)"; }
    if [ $fail -eq 0 ]; then PASS=$((PASS+1)); echo -e "  ${G}✓${N} [VG] $name"
    else FAIL=$((FAIL+1)); echo -e "  ${R}✗${N} [VG] $name"; echo -e "    ${Y}→ $reason${N}"; ERRORS="$ERRORS\n  ✗ [VG] $name: $reason"; fi
}

rm -f /tmp/ms_* vg.txt

echo -e "\n${C}${B}═══════════════════════════════════════════════${N}"
echo -e "${C}${B}       MINISHELL COMPREHENSIVE TEST SUITE v6    ${N}"
echo -e "${C}${B}═══════════════════════════════════════════════${N}\n"

###############################################################################
echo -e "${C}━━ ECHO (12 tests) ━━${N}"
###############################################################################
test_exact   "echo hello"           "echo hello"            "hello"         "0"
test_exact   "echo multi words"     "echo hello world"      "hello world"   "0"
test_vs_bash "echo (newline)"       "echo"
test_echo_n  "echo -n hello"        "echo -n hello"         "hello"
test_echo_n  "echo -n -n -n hello"  "echo -n -n -n hello"   "hello"
test_echo_n  "echo -nnnnn hello"    "echo -nnnnn hello"     "hello"
test_exact   "echo dquoted"         'echo "hello world"'    "hello world"   "0"
test_exact   "echo squoted"         "echo 'hello world'"    "hello world"   "0"
test_exact   "echo mixed quotes"    "echo \"hello\"'world'" "helloworld"    "0"
test_vs_bash "echo empty dquotes"   'echo ""'
test_vs_bash "echo empty squotes"   "echo ''"
test_exact   "echo spaces"          "echo hello    world"   "hello world"   "0"

###############################################################################
echo -e "\n${C}━━ PWD (1 test) ━━${N}"
###############################################################################
test_exact  "pwd"                   "pwd"                   "$(pwd)"        "0"

###############################################################################
echo -e "\n${C}━━ CD (6 tests) ━━${N}"
###############################################################################
test_exact  "cd HOME + pwd"  "cd
pwd"  "$HOME"  "0"
test_exact  "cd / + pwd"    "cd /
pwd"  "/"      "0"
test_exact  "cd /tmp + pwd" "cd /tmp
pwd"  "/tmp"   "0"
test_exact  "cd .. from /tmp" "cd /tmp
cd ..
pwd"  "/"      "0"
test_exact  "cd nonexistent \$?=1" "cd /nonexistent_xyz
echo \$?"  "1"  "0"
test_exact  "cd too many args" "cd a b
echo \$?"  "1"  "0"

###############################################################################
echo -e "\n${C}━━ EXIT STATUS (5 tests) ━━${N}"
###############################################################################
test_exact  "\$?=0 after echo"  "echo hello
echo \$?"  "hello
0"  "0"
test_exact  "\$?=1 after false" "/bin/false
echo \$?"  "1"  "0"
test_exact  "\$?=0 after true"  "/bin/true
echo \$?"  "0"  "0"
test_exact  "\$?=127 bad cmd"   "nonexistent_xyz
echo \$?"  "127"  "0"
test_exact  "\$?=1 cd fail"     "cd /no_such_dir
echo \$?"  "1"  "0"

###############################################################################
echo -e "\n${C}━━ EXPANSION (11 tests) ━━${N}"
###############################################################################
test_exact  "\$HOME"                'echo $HOME'                    "$HOME"             "0"
test_exact  "\$USER"                'echo $USER'                    "$USER"             "0"
test_vs_bash "\$PATH"               'echo $PATH'
test_exact  "undef var=empty"       'echo $UNDEF_XYZ'              ""                  "0"
test_exact  "\$?=0"                 'echo $?'                       "0"                 "0"
test_vs_bash "dollar at end"        'echo hello$'
test_exact  "\$USER in dquotes"     'echo "$USER"'                  "$USER"             "0"
test_exact  "\$USER in squotes"     "echo '\$USER'"                 '$USER'             "0"
test_exact  "text+\$USER+text"      'echo "hello $USER end"'        "hello $USER end"   "0"
test_exact  "adjacent vars"         'echo $USER$HOME'               "${USER}${HOME}"    "0"
test_vs_bash "\$? after pipe fail"  '/bin/false | /bin/true
echo $?'

###############################################################################
echo -e "\n${C}━━ PIPES (10 tests) ━━${N}"
###############################################################################
test_exact  "echo | cat"            "echo hello | cat"              "hello"         "0"
test_exact  "echo | grep"           "echo hello world | grep hello" "hello world"   "0"
test_vs_bash "echo | wc -l"         "echo hello | wc -l"
test_exact  "4-stage pipe"          "echo hello | cat | cat | cat"  "hello"         "0"
test_vs_bash "ls | head -1"         "ls | head -1"
test_vs_bash "cat file | head"      "cat /etc/passwd | head -3"
test_vs_bash "echo | wc -c"         "echo hello | wc -c"
test_exact  "echo|tr|rev"           "echo abc | tr a-z A-Z | rev"  "CBA"           "0"
test_vs_bash "pipe status=last"     "echo hi | /bin/false
echo \$?"
test_vs_bash "false|echo hi"        "/bin/false | echo hi"

###############################################################################
echo -e "\n${C}━━ OUTPUT REDIR (4 tests) ━━${N}"
###############################################################################
test_exact  "echo > file"          "echo hello > /tmp/ms_o1
cat /tmp/ms_o1"  "hello"  "0"
test_vs_bash "echo >> append"      "echo l1 > /tmp/ms_o2
echo l2 >> /tmp/ms_o2
cat /tmp/ms_o2"
test_exact  "overwrite"            "echo first > /tmp/ms_o3
echo second > /tmp/ms_o3
cat /tmp/ms_o3"  "second"  "0"
test_exact  "multi > (last wins)"  "echo aaa > /tmp/ms_o4a > /tmp/ms_o4b
cat /tmp/ms_o4b" "aaa" "0"

###############################################################################
echo -e "\n${C}━━ INPUT REDIR (3 tests) ━━${N}"
###############################################################################
echo "test content" > /tmp/ms_i1
test_exact  "cat < file"           "cat < /tmp/ms_i1"       "test content"  "0"
printf "l1\nl2\nl3\n" > /tmp/ms_i2
test_vs_bash "cat < multiline"     "cat < /tmp/ms_i2"
test_exact  "< nonexistent \$?=1"  "cat < /tmp/ms_nofile_xyz
echo \$?"  "1"  "0"

###############################################################################
echo -e "\n${C}━━ COMBINED REDIR (2 tests) ━━${N}"
###############################################################################
echo "combo" > /tmp/ms_c1
test_exact  "cat < in > out"       "cat < /tmp/ms_c1 > /tmp/ms_c1o
cat /tmp/ms_c1o"  "combo"  "0"
test_vs_bash "echo>file; cat|wc"   "echo hello world > /tmp/ms_c2
cat /tmp/ms_c2 | wc -w"

###############################################################################
echo -e "\n${C}━━ HEREDOC (5 tests) ━━${N}"
###############################################################################
# Heredoc tests use > file to avoid readline prompt echo in non-tty mode
test_exact  "heredoc basic"        "$(printf 'cat << EOF > /tmp/ms_hd1\nhello\nEOF\ncat /tmp/ms_hd1')"          "hello"     "0"
test_exact  "heredoc multiline"    "$(printf 'cat << END > /tmp/ms_hd2\nline1\nline2\nline3\nEND\ncat /tmp/ms_hd2')"  "line1
line2
line3"  "0"
test_exact  "heredoc + \$USER"     "$(printf 'cat << EOF > /tmp/ms_hd3\n$USER\nEOF\ncat /tmp/ms_hd3')"          "$USER"     "0"
test_exact  "heredoc + pipe"       "$(printf 'cat << EOF | cat\nhello\nEOF')"           "hello"     "0"
test_exact  "heredoc quoted delim" "$(printf "cat << 'EOF' > /tmp/ms_hd4\n\$USER\nEOF\ncat /tmp/ms_hd4")"       '$USER'     "0"

###############################################################################
echo -e "\n${C}━━ EXIT BUILTIN (7 tests) ━━${N}"
###############################################################################
test_exact  "exit -> 0"            "exit"                  ""      "0"
test_exact  "exit 42"              "exit 42"               ""      "42"
test_exact  "exit 0"               "exit 0"                ""      "0"
test_exact  "exit 255"             "exit 255"              ""      "255"
test_exact  "exit 256 -> 0"        "exit 256"              ""      "0"
test_exact  "exit -1 -> 255"       "exit -1"               ""      "255"
test_exact  "exit abc -> 2"        "exit abc"              ""      "2"

###############################################################################
echo -e "\n${C}━━ EDGE CASES (4 tests) ━━${N}"
###############################################################################
test_vs_bash "empty input"         ""
test_vs_bash "only spaces"         "   "
test_exact  "/bin/echo"            "/bin/echo hello"        "hello"  "0"
test_exact  "nonexistent \$?"      "totally_fake_cmd
echo \$?"  "127"  "0"

###############################################################################
echo -e "\n${C}━━ ENV BUILTIN (3 tests) ━━${N}"
###############################################################################
test_vs_bash "env | wc -l"         "env | wc -l"
test_vs_bash "env | grep PATH"     "env | grep ^PATH= | wc -l"
test_vs_bash "env | grep HOME"     "env | grep ^HOME= | wc -l"

###############################################################################
echo -e "\n${C}━━ SYNTAX ERRORS (8 tests) ━━${N}"
###############################################################################
test_exact  "pipe at start"        "| echo hello"         ""  "2"
test_exact  "double pipe"          "echo || echo"         ""  "2"
test_exact  "redir no file"        "echo hello >"         ""  "2"
test_exact  "double redir"         "echo hello >> >"      ""  "2"
test_exact  "pipe at end"          "echo hello |"         ""  "2"
test_exact  "unclosed squote"      "echo 'hello"          ""  "2"
test_exact  "unclosed dquote"      'echo "hello'          ""  "2"
test_exact  "< < consecutive"      "cat < < file"         ""  "2"

###############################################################################
echo -e "\n${C}━━ EXTRA EXPANSION EDGE CASES (6 tests) ━━${N}"
###############################################################################
test_exact  "empty var in dquotes"  'echo "$UNDEF_XYZ"'          ""          "0"
test_exact  "dollar alone"          'echo $'                     '$'         "0"
test_exact  "\$? chained"           '/bin/false
/bin/true
echo $?'  "0"  "0"
test_exact  "mixed quote types"     "echo \"'hello'\""           "'hello'"   "0"
test_exact  "squote inside dquote"  "echo \"it's working\""      "it's working" "0"
test_exact  "dquote inside squote"  'echo '"'"'"hello"'"'"''     '"hello"'   "0"

###############################################################################
echo -e "\n${C}━━ EXTRA PIPE EDGE CASES (4 tests) ━━${N}"
###############################################################################
test_exact  "5-stage pipe"         "echo hello | cat | cat | cat | cat" "hello" "0"
test_exact  "pipe with redir"      "echo hello | cat > /tmp/ms_pr1
cat /tmp/ms_pr1" "hello" "0"
test_vs_bash "pipe + grep -c"      "echo -e 'a\nb\nc' | grep -c ''"
test_exact  "echo pipe wc -w"      "echo one two three | wc -w" "3" "0"

###############################################################################
echo -e "\n${C}━━ EXTRA REDIR EDGE CASES (4 tests) ━━${N}"
###############################################################################
test_exact  ">> creates file"      "echo first >> /tmp/ms_app_new
cat /tmp/ms_app_new" "first" "0"
test_exact  "multi input redir"    "echo aaa > /tmp/ms_mi1
echo bbb > /tmp/ms_mi2
cat < /tmp/ms_mi1 < /tmp/ms_mi2" "bbb" "0"
test_exact  "redir before cmd"     "> /tmp/ms_rb1 echo hello
cat /tmp/ms_rb1" "hello" "0"
test_exact  "empty cmd with redir" "> /tmp/ms_empty_redir
cat /tmp/ms_empty_redir" "" "0"

###############################################################################
echo -e "\n${C}${B}═══════════════════════════════════════════${N}"
echo -e "${C}${B}       VALGRIND: MEMORY & FD LEAKS         ${N}"
echo -e "${C}${B}═══════════════════════════════════════════${N}\n"
###############################################################################

echo -e "${C}━━ Memory Leak Tests (23) ━━${N}"
run_valgrind "echo hello"          "echo hello"
run_valgrind "echo \$HOME"         'echo $HOME'
run_valgrind "pwd"                 "pwd"
run_valgrind "cd /tmp + pwd"       "cd /tmp
pwd"
run_valgrind "cd (home)"           "cd"
run_valgrind "cd nonexist"         "cd /no_such_dir"
run_valgrind "pipe: echo|cat"      "echo hello | cat"
run_valgrind "pipe: echo|cat|cat"  "echo hi | cat | cat"
run_valgrind "echo > file"         "echo test > /tmp/ms_v1"
run_valgrind "cat < file"          "echo data > /tmp/ms_v_in
cat < /tmp/ms_v_in"
run_valgrind "echo >> file"        "echo a >> /tmp/ms_v2
echo b >> /tmp/ms_v2"
run_valgrind "cat < in > out"      "echo x > /tmp/ms_v_ci
cat < /tmp/ms_v_ci > /tmp/ms_v_co"
run_valgrind "pipe + redir"        "echo hello | cat > /tmp/ms_v3"
run_valgrind "bad cmd"             "fake_command"
run_valgrind "multi echo"          "echo a
echo b
echo c"
run_valgrind "\$? expand"          'echo $?'
run_valgrind "dquotes"             'echo "hello"'
run_valgrind "squotes"             "echo 'hello'"
run_valgrind "false+\$?"           "/bin/false
echo \$?"
run_valgrind "env | head"          "env | head -1"
run_valgrind "heredoc"             "$(printf 'cat << EOF\nhello\nEOF')"
run_valgrind "heredoc+pipe"        "$(printf 'cat << EOF | cat\nhello\nEOF')"
run_valgrind "vars"                'echo "$HOME" $USER'

echo -e "\n${C}━━ FD Leak Stress (8) ━━${N}"
run_valgrind "5-pipe"              "echo a | cat | cat | cat | cat"
run_valgrind "5 redirs"            "echo a > /tmp/ms_s1
echo b > /tmp/ms_s2
echo c > /tmp/ms_s3
echo d > /tmp/ms_s4
echo e > /tmp/ms_s5"
run_valgrind "pipe+redir x2"       "ls | cat > /tmp/ms_s6
ls | cat > /tmp/ms_s7"
run_valgrind "in+out redir"        "echo hi > /tmp/ms_s8
cat < /tmp/ms_s8 > /tmp/ms_s9"
run_valgrind "syntax error"        "| echo hello"
run_valgrind "bad redir"           "cat < /tmp/ms_nonexistent_vg"
run_valgrind "empty input"         ""
run_valgrind "multi pipe+redir"    "echo a | cat > /tmp/ms_vfd1
echo b >> /tmp/ms_vfd1
cat < /tmp/ms_vfd1 | cat | cat"

# Cleanup
rm -f /tmp/ms_* vg.txt

###############################################################################
echo -e "\n${C}${B}═══════════════════════════════════════════${N}"
echo -e "${C}${B}              FINAL RESULTS                ${N}"
echo -e "${C}${B}═══════════════════════════════════════════${N}"
echo -e "  ${B}Total:  $TOTAL${N}"
echo -e "  ${G}${B}Passed: $PASS${N}"
echo -e "  ${R}${B}Failed: $FAIL${N}"
if [ $FAIL -gt 0 ]; then
    echo -e "\n${R}${B}── Failed Tests ──${N}"
    echo -e "$ERRORS"
fi
echo ""

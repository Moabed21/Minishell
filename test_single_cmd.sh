#!/bin/bash
# Minishell single-command test suite
# Uses script(1) to provide a PTY so isatty() passes

MINI="./minishell"
PASS=0
FAIL=0
TOTAL=0

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Run a command in minishell via a pseudo-terminal
run_in_mini() {
    local cmd="$1"
    # Use script to create a PTY, send the command + exit, capture output
    local out
    out=$(script -qec "printf '%s\nexit\n' '$cmd' | timeout 5 $MINI" /dev/null 2>/dev/null)
    # Strip the prompt lines and exit lines
    echo "$out" | grep -v '^minishell>' | grep -v '^exit$' | sed '/^$/d'
}

run_test() {
    local desc="$1"
    local cmd="$2"
    TOTAL=$((TOTAL + 1))

    bash_out=$(echo "$cmd" | bash 2>/dev/null)
    mini_out=$(run_in_mini "$cmd")

    bash_trimmed=$(echo "$bash_out" | sed 's/[[:space:]]*$//' | head -5)
    mini_trimmed=$(echo "$mini_out" | sed 's/[[:space:]]*$//' | head -5)

    if [ "$bash_trimmed" = "$mini_trimmed" ]; then
        echo -e "${GREEN}[PASS]${NC} $desc"
        PASS=$((PASS + 1))
    else
        echo -e "${RED}[FAIL]${NC} $desc"
        echo "       CMD:      '$cmd'"
        echo "       EXPECTED: '$(echo "$bash_trimmed" | head -2)'"
        echo "       GOT:      '$(echo "$mini_trimmed" | head -2)'"
        FAIL=$((FAIL + 1))
    fi
}

echo "============================================"
echo "  MINISHELL SINGLE COMMAND TESTS"
echo "============================================"
echo ""

echo -e "${YELLOW}--- Basic External Commands ---${NC}"
run_test "echo hello" "echo hello"
run_test "echo hello world" "echo hello world"
run_test "echo -n hello" "echo -n hello"
run_test "echo (no args)" "echo"
run_test "/bin/echo direct path" "/bin/echo direct path"
run_test "ls / (first 3 lines)" "ls /"
run_test "pwd" "pwd"
run_test "whoami" "whoami"
run_test "uname" "uname"

echo ""
echo -e "${YELLOW}--- Builtin Commands ---${NC}"
run_test "pwd builtin" "pwd"
run_test "env first line" "env"

echo ""
echo -e "${YELLOW}--- Redirections ---${NC}"

# Test > redirect
rm -f /tmp/mini_test_redir
TOTAL=$((TOTAL + 1))
script -qec "printf 'echo hello redir > /tmp/mini_test_redir\nexit\n' | timeout 5 $MINI" /dev/null > /dev/null 2>&1
redir_content=$(cat /tmp/mini_test_redir 2>/dev/null)
if [ "$redir_content" = "hello redir" ]; then
    echo -e "${GREEN}[PASS]${NC} echo > file"
    PASS=$((PASS + 1))
else
    echo -e "${RED}[FAIL]${NC} echo > file"
    echo "       EXPECTED: 'hello redir'"
    echo "       GOT:      '$redir_content'"
    FAIL=$((FAIL + 1))
fi

# Test < redirect
echo "input file content" > /tmp/mini_test_input
TOTAL=$((TOTAL + 1))
mini_cat=$(run_in_mini "cat < /tmp/mini_test_input")
if echo "$mini_cat" | grep -q "input file content"; then
    echo -e "${GREEN}[PASS]${NC} cat < file"
    PASS=$((PASS + 1))
else
    echo -e "${RED}[FAIL]${NC} cat < file"
    echo "       EXPECTED contains: 'input file content'"
    echo "       GOT: '$mini_cat'"
    FAIL=$((FAIL + 1))
fi

# Test >> append
rm -f /tmp/mini_test_append
TOTAL=$((TOTAL + 1))
script -qec "printf 'echo first > /tmp/mini_test_append\necho second >> /tmp/mini_test_append\nexit\n' | timeout 5 $MINI" /dev/null > /dev/null 2>&1
append_content=$(cat /tmp/mini_test_append 2>/dev/null)
if [ "$append_content" = "first
second" ]; then
    echo -e "${GREEN}[PASS]${NC} echo >> file (append)"
    PASS=$((PASS + 1))
else
    echo -e "${RED}[FAIL]${NC} echo >> file (append)"
    echo "       EXPECTED: 'first\\nsecond'"
    echo "       GOT:      '$append_content'"
    FAIL=$((FAIL + 1))
fi

echo ""
echo -e "${YELLOW}--- Command Not Found ---${NC}"
TOTAL=$((TOTAL + 1))
notfound=$(run_in_mini "nonexistent_cmd_xyz_abc" 2>&1)
if echo "$notfound" | grep -qi "not found"; then
    echo -e "${GREEN}[PASS]${NC} command not found error"
    PASS=$((PASS + 1))
else
    echo -e "${RED}[FAIL]${NC} command not found error"
    echo "       GOT: '$notfound'"
    FAIL=$((FAIL + 1))
fi

echo ""
echo -e "${YELLOW}--- Edge Cases ---${NC}"
run_test "echo with many spaces" "echo    hello     world"
run_test "echo -n -n -n hi" "echo -n -n -n hi"

echo ""
echo "============================================"
echo -e "  RESULTS: ${GREEN}$PASS passed${NC}, ${RED}$FAIL failed${NC}, $TOTAL total"
echo "============================================"

# Cleanup
rm -f /tmp/mini_test_redir /tmp/mini_test_input /tmp/mini_test_append

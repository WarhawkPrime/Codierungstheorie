# Code formatting

Using [clang-format](https://clang.llvm.org/docs/ClangFormat.html)

```shell
clang-format -i **/**.cpp **/**.h
```

Using the following githook is recommended:
`REPO_ROOT/.git/hooks/pre-commit`

```shell
#!/bin/sh
# Automatic formatting for changed files

# See: https://unix.stackexchange.com/questions/9496/looping-through-files-with-spaces-in-the-names for and explanation
OIFS="$IFS" # This shit is because of spaces in
IFS=$'\n'   # file names looking at you @Dennis

for FILE in $(git diff --cached --name-only | grep -E '.*\.(c|cpp|h|hpp)\b')
do
        escFN=\'${FILE}\'
        clang-format -i \'${escFN}\'
done

IFS="$OIFS" # Retun to normal bash behavior...
```

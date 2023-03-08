#!/bin/bash

DEBUG_OUTPUT=false

PROJECT_PATH=""
PROJECT_NAME=""
CURRENT_PATH="${PWD}"

languages=()
compilers=()
compiled_files=()

addLanguages() {
  compiler=${1##*=}
  new_languages=${1%=*}
  for language in ${new_languages//=/ }; do
    languages+=( "${language}" )
    compilers+=( "${compiler}" )
  done
}

# this is debug function
outputLanguages() {
  if [ "${DEBUG_OUTPUT}" = true ]; then
    echo "compiler accordance: "
    for (( i=0; i<${#languages[*]}; i++ )); do
      echo "${languages[${i}]}: ${compilers[${i}]}"
    done
  fi
}

parseInput() {
  counter=0;
  while (( $# > 0 )); do
    if [ "$counter" -eq "1000" ]; then
      echo "Incorrect input"
      exit 1
    fi
    counter=$((counter+1))
    if [ "$1" = "--source" ] || [ "$1" = "-s" ]; then
      PROJECT_PATH="$2"
    fi
    if [ "$1" = "--archive" ] || [ "$1" = "-a" ]; then
      PROJECT_NAME="$2"
    fi
    if [ "$1" = "--compiler" ] || [ "$1" = "-c" ]; then
      addLanguages "$2"
    fi
    shift 2
  done
}

compileFile() {
  if [ "${DEBUG_OUTPUT}" = true ]; then
    echo "file to compile: $1 with $2"
  fi
  new_binary="${file%.$3}.exe"
  if [ "${DEBUG_OUTPUT}" = true ]; then
    echo "$2 -o ${new_binary} $1"
  fi
  eval "$2 -o ${new_binary} $1"
  compiled_files+=( "$(realpath --relative-to "$PROJECT_PATH" "${new_binary}")" )
  if [ "${DEBUG_OUTPUT}" = true ]; then
    echo "OK file $1"
  fi
}

parseInput "$@"

# some config information
if [ "${DEBUG_OUTPUT}" = true ]; then
  echo "Project path is: ${PROJECT_PATH}"
  echo "Project will be made in this directory in folder: ${CURRENT_PATH}/${PROJECT_NAME}"
  echo ""

  outputLanguages
  echo ""
fi
# some confing information

# compile all files
for (( i=0; i<${#languages[*]}; i++ )); do
  files=$(find "$PROJECT_PATH" -name "*.${languages[$i]}")
  for file in ${files[*]}; do
    compileFile "${file}" "${compilers[$i]}" "${languages[$i]}"
  done
done
# compile all files

if [ "${DEBUG_OUTPUT}" = true ]; then
  echo "${compiled_files[*]}"
fi

tar -zcf "$PROJECT_NAME.tar.gz" -C "$PROJECT_PATH" --transform "s,^,$PROJECT_NAME/," "${compiled_files[@]}"

# deleting all files
for (( i=0; i<${#languages[*]}; i++ )); do
  files=$(find "$PROJECT_PATH" -name "*.${languages[$i]}")
  for file in ${files[*]}; do
    eval rm "${file%."${languages[$i]}"}.exe"
  done
done
# deleting all files

echo "complete"
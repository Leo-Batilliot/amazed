#!/bin/bash

# Path to the binary
binary_path="./amazed"
# Authorized functions
authorized="read|write|malloc|free|getline"
# Status of the script
status=0
# List of keywords reserved by C
reserved_keywords="if|for|while|switch|return|else|sizeof|void|va_*"

# Checks for authorized functions
is_function_authorized() {
  local func=$1
  
  if echo "$func" | grep -qE "$authorized"; then
    return 0  # Authorized function
  else
    return 1  # Banned function
  fi
}

# Verifies if a function is a standard C library function (by checking inside man 2 or man 3)
is_standard_lib_function() {
  local func=$1

  if man 2 "$func" 2>/dev/null | grep -q "$func" || man 3 "$func" 2>/dev/null | grep -q "$func"; then
    return 0  # Found
  else
    return 1  # Not found
  fi
}

# Extracts all function calls from the binary using objdump
objdump -d "$binary_path" | grep -oP '\b\w+\b(?=\@plt)' | grep -Ev "$reserved_keywords" | sort -u | while read func; do
  # Checks if the function is a standard C library function and if it is authorized
  if is_standard_lib_function "$func" && ! is_function_authorized "$func"; then
    # Outputs the function
    echo $func >> banned_funcs.log
  fi
done

# Exit with the status
exit $status
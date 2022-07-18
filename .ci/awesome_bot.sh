#!/bin/bash

awesome_bot_with_retry() {
  local attempt_max=5
  local -i attempt_num=1
  until awesome_bot "$@"; do
      if ((attempt_num == attempt_max)); then
          exit 1
      fi
      echo "retry ${attempt_num}"
      ((attempt_num++))
  done
}

awesome_bot_with_retry "$@"

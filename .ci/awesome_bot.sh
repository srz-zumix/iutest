#!/bin/bash

if type awesome_bot >/dev/null 2>&1; then
  AWESOME_BOT_EXEC="awesome_bot"
else
  AWESOME_BOT_EXEC="bundle exec awesome_bot"
fi

awesome_bot_with_retry() {
  local attempt_max=5
  local -i attempt_num=1
  until ${AWESOME_BOT_EXEC} "$@"; do
      if ((attempt_num == attempt_max)); then
          exit 1
      fi
      echo "retry ${attempt_num}"
      ((attempt_num++))
  done
}

awesome_bot_with_retry "$@"

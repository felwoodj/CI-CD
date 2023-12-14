#!/bin/bash

TELEGRAM_BOT_TOKEN="6010959177:AAEoOEE_sCjXNQScT0_xgMwgJHSylPjb_Dg"
TELEGRAM_USER_ID="537413026"

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Deploy status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AStatus:+$CI_JOB_STATUS%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"

curl -s -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null

# -s не выводит информацию об процессе отправки запроса
#  -d какие параметры мы передаем в теле запроса
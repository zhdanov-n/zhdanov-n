#!/bin/bash

BOT_TOKEN="6793611031:AAGx37Me-mz15IkvoKwYvO-M5tnmRZMDFyY"
URL="https://api.telegram.org/bot$BOT_TOKEN/sendMessage"
ID="178527657"

if [[ $CI_JOB_STATUS = "success" ]]; then
    STATUS=✅
else
    STATUS=❌
fi

TEXT="Job: $1 $STATUS%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"

curl -s -d "chat_id=$ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
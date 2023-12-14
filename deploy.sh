#!/usr/bin/expect -f
# скрипт выполняется с помощью интерпретатора except
# флаг -f указывает что это скрипт

# присваиваем переменной password наш пароль
set password "Oirat2014@)!%"

# запускаем подключение к 2 машине через ssh
# ожидаем запрос на подвтерждение и нажимаем yes
# ожидаем пароль, отправляем его
# ожидаем завершения выполнения команды
spawn ssh ws@10.20.0.20
expect {
        "*fingerprint*" { send -- "yes\r" }
}
expect "password:"
send "$password\r"

spawn scp src/cat/s21_cat src/grep/s21_grep ws@10.20.0.20:/usr/local/bin
expect "password:"
send "$password\r"

spawn ssh ws@10.20.0.20 ls -lah /usr/local/bin
expect "password:"
send "$password\r"
expect eof 
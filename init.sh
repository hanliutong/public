#!/bin/bash
sudo apt-get update
sudo apt update
sudo apt-get install python-pip
sudo apt-get install python-setuptools
pip install shadowsocks
sed -i "s/cleanup/reset/g" /usr/local/lib/python2.7/dist-packages/shadowsocks/crypto/openssl.py
my_ip=`ifconfig | grep inet | grep -v inet6 | grep -v 127 | cut -d ' '  -f10`
printf "{
\"server\":\"$my_ip\",
\"server_port\":8080,
\"local_address\": \"127.0.0.1\",
\"local_port\":1080,
\"password\":\"qwer1234\",
\"timeout\":300,
\"method\":\"aes-256-cfb\",
\"fast_open\": false
}
" > /etc/ss.json
ssserver -c /etc/ss.json -d restart

printf "
#!/bin/bash
printf \"{
\"server\":\"$my_ip\",
\"server_port\":\$1,
\"local_address\": \"127.0.0.1\",
\"local_port\":1080,
\"password\":\"qwer1234\",
\"timeout\":300,
\"method\":\"aes-256-cfb\",
\"fast_open\": false
}
\" > /etc/ss.json

ssserver -c /etc/ss.json -d restart

">/root/ss.sh
chmod +x /root/ss.sh

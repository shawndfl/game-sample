#!/bin/bash

echo "Required:"
echo "sudo apt install nginx  php-curl php7.2-fpm"
echo 

home_base=$(cd $(dirname $0); pwd -P)
site_name=mysite.com

sudo cp ${home_base}/${site_name} /etc/nginx/sites-available/${site_name}
if [ ! -f /etc/nginx/sites-enabled/${site_name} ]; then
	sudo ln -s /etc/nginx/sites-available/${site_name} /etc/nginx/sites-enabled/${site_name}
fi

sudo sed -i 's:{{WWW_ROOT}}:'${home_base}'/www:' /etc/nginx/sites-available/${site_name}

sudo rm -f /etc/nginx/sites-enabled/default
sudo systemctl restart nginx.service
sudo systemctl restart php7.2-fpm

sudo nginx -t
#!/bin/bash

home_base=$(cd $(dirname $0); pwd -P)
site_name=mysite.com

sudo cp ${home_base}/${site_name} /etc/nginx/sites-available/${site_name}
if [ ! -f /etc/nginx/sites-enabled/${site_name} ]; then
	sudo ln -s /etc/nginx/sites-available/${site_name} /etc/nginx/sites-enabled/${site_name}
fi

sudo sed -i 's:{{WWW_ROOT}}:'${home_base}'/www:' /etc/nginx/sites-enabled/${site_name}
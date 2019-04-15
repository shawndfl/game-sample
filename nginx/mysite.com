server {
        listen 80 default_server;
        listen [::]:80 default_server;        
        
        root {{WWW_ROOT}};
        
        index index.php;
        
        server_name localhost 127.0.0.1;

        location / {
                try_files $uri $uri/ =404;
        }

        location ~ \.php$ {
            fastcgi_pass unix:/run/php/php7.2-fpm.sock;
            include snippets/fastcgi-php.conf;
            fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        }

        location ~ /\.ht {
                deny all;
        }
}
***Question: How would you set up this site, with one code base, that caters to different markets such as GB, FR and DE? Describe:***

There are 2 ways doing this. It depends on whether those markets have to share content.  
The first way is using Domain Access module. The benefit of using domain access is this one can share same content and same database.   

The second way is create multi-site folders. The benefit of doing this is this can separate data in different database and optionally share same table such as the `users`.   

In the case for multi-site type stated in background, we have to create a subdirectory for multi-sites with symbolic link by   
```ln -s . subdir```  
Then update the .htaccess to ignore the subdir in rewrite rule.   
```RewriteRule ^ subdir/index.php [L]```  


***Follow up 1. Apache configuration especially Virtual Host configuration. Give statements that you would use in the Apache conf file.***
-------
```
    <VirtualHost *:80>
      DocumentRoot /var/www/public_html
      ServerName example.com
      ServerAlias www.example.com
      ServerAdmin daeus@example.com
      RewriteEngine On
      ErrorLog /var/log/apache2/error.log
      LogLevel warn
      CustomLog /var/log/apache2/access.log combined
      ServerSignature On
      <Directory /var/www/public_html>
        AllowOverride All
        Require all granted
      </Directory>
    </VirtualHost>
```

In case if we have to setup multi-site with different server name(like example.co.uk, example.de), we have to set this up in this way 
```
    <VirtualHost *:80>
      DocumentRoot /var/www/public_html
      ServerName example.co.uk
      ServerAlias www.example.co.uk
      ServerAdmin daeus@example.co.uk
      RewriteEngine On
      ErrorLog /var/log/apache2/example_uk_error.log
      LogLevel warn
      CustomLog /var/log/apache2/example_uk_access.log combined
      ServerSignature On
      <Directory /var/www/public_html>
        AllowOverride All
        Require all granted
      </Directory>
    </VirtualHost>
    <VirtualHost *:80>
      DocumentRoot /var/www/public_html
      ServerName example.de
      ServerAlias www.example.de
      ServerAdmin daeus@example.de
      RewriteEngine On
      ErrorLog /var/log/apache2/example_de_error.log
      LogLevel warn
      CustomLog /var/log/apache2/example_de_access.log combined
      ServerSignature On
      <Directory /var/www/public_html>
        AllowOverride All
        Require all granted
      </Directory>
    </VirtualHost>
```
Where they share the same document root with different server name.

***Follow up 2: Drupal folder setup - how you would set up the folder structure***
For the solution of using module Domain Access, we don't have to set up the specific folder structure.
For the multi-site folders solution, we have to create specific folders for different markets in sites folder.
The structure would be look like this:
```
└──sites
    ├── all
    ├── example.com.gb
    ├── example.com.fr
    └── example.com.de

``` 

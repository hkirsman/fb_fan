
Themeable Facebook Fan Box
==========================

This module allows you to embed Facebook Fan Box to your site and optionally
apply custom styles. It uses Facebooks fb:fan tag which allows one to pull in
external CSS file.


Requirements
============

* http://drupal.org/project/fb


How to use
==========

1. Get facebook-php-sdk from https://github.com/facebook/facebook-php-sdk
   and copy it to sites/all/libraries/facebook-php-sdk
2. Get Drupal for Facebook module from http://drupal.org/project/fb and
   enable it.
3. Add app under admin/structure/fb/fb_app_create (It's important to check
   "Primary" under "Facebook connect"!)
4. Add Fan Box under admin/structure/fb/fb_fan/create.
5. Getting your page id is a bit tricky. It's a number eg 259175840792045.
   Look at the url of your facebook page. If you see a number there then you've
   found your page id. For example it's 8427738891 for
   http://www.facebook.com/pages/Drupal/8427738891. If you have page like
   http://www.facebook.com/nike, then you have to go to
   https://graph.facebook.com/nike and look up line where it says id.
6. Fill in rest of the settings and hit save. CSS path is optional. It has to
   be full url and publicly accessible.
7. Go to blocks page and enable your new fan box.

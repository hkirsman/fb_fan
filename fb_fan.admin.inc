<?php
/**
 * @file
 * Admin pages and forms for Drupal for fb_fan.
 *
 */


/**
 * Drupal page callback.
 */
function fb_fan_admin_page_list() {
  $header = array('Name', 'Profile ID', 'Edit');
  $rows = array();
  $fanboxes = variable_get('fb_fan_fanboxes', array());
  foreach($fanboxes as $id => $fanbox) {
    $rows[] = array(
      $fanbox['fb_fan_name'],
      $fanbox['fb_fan_profile_id'],
      l('Edit', FB_PATH_ADMIN . '/fb_fan/list/' . $id . '/edit'),
    );
  }
  return theme('table', array('header' => $header, 'rows' => $rows));
}

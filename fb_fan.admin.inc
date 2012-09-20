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
  $apps = fb_get_all_apps();
  if (count($apps) == 0) {
    drupal_set_message(t("Fan Boxes need application. Please !create one now!", array('!create' => l('create', FB_PATH_ADMIN . '/fb_app_create'))), 'warning');
  }
  drupal_set_title(t('List Fan Boxes'));
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

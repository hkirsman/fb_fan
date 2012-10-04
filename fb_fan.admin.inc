<?php
/**
 * @file
 * Admin pages and forms for Drupal for fb_fan.
 */


/**
 * Drupal page callback for listing fan boxes.
 */
function fb_fan_admin_page_list() {
  fb_fan_check_if_fb_application_exists();
  drupal_set_title(t('List Fan Boxes'));
  $header = array('Name', 'Profile ID', 'Edit', 'Delete');
  $rows = array();
  $fanboxes = variable_get('fb_fan_fanboxes', array());
  foreach ($fanboxes as $id => $fanbox) {
    $rows[] = array(
      $fanbox['fb_fan_name'],
      $fanbox['fb_fan_profile_id'],
      l(t('Edit'), FB_PATH_ADMIN . '/fb_fan/list/edit/' . $id),
      l(t('Delete'), FB_PATH_ADMIN . '/fb_fan/delete/' . $id),
    );
  }
  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Drupal page callback for deleting fan box.
 */
function fb_fan_admin_page_delete($fb_fan_id = FALSE) {
  $fanboxes = variable_get('fb_fan_fanboxes', array());
  if (count($fanboxes)) {
    if (array_key_exists($fb_fan_id, $fanboxes)) {
      unset($fanboxes[$fb_fan_id]);
      variable_set('fb_fan_fanboxes', $fanboxes);
      drupal_set_message(t('Fan Box deleted successfully.'));
      drupal_goto(FB_PATH_ADMIN . '/fb_fan/list');
      die();
    }
  }
  drupal_set_message(t('Could not delete!', 'error'));
  drupal_goto(FB_PATH_ADMIN . '/fb_fan/list');
}

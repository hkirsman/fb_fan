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

/**
 * Form for create and editing fan box.
 */
function fb_fan_edit_fanbox_form($form, &$form_state, $is_edit = FALSE) {
  fb_fan_check_if_fb_application_exists();

  $fanboxes = variable_get('fb_fan_fanboxes', array());
  if ($is_edit && is_numeric(arg(6))) {
    drupal_set_title(t('Edit Fan Box'));
    $fanbox_id = arg(6);
  }
  elseif ($is_edit) {
    drupal_set_message('Wrong url. No id set in url.');
    return FALSE;
  }
  else {
    // Create page.
    drupal_set_title(t('Create Fan Box'));
    $fanbox_id = 'temp';
    $fanboxes[$fanbox_id] = array(
      'fb_fan_name' => '',
      'fb_fan_profile_id' => '',
      'fb_fan_connections' => '10',
      'fb_fan_width' => '200',
      'fb_fan_height' => '400',
      'fb_fan_css_path' => '',
      'fb_fan_stream' => '1',
      'fb_fan_logo' => '1',
      'fb_fan_header' => '1',
    );
  }

  $form['fb_fan_general_settings'] = array(
    '#title' => t('General Settings'),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
  );
  $form['fb_fan_general_settings']['is_edit'] = array(
    '#type' => 'hidden',
    '#required' => TRUE,
    '#default_value' => $is_edit ? '1' : '0',
  );
  $form['fb_fan_general_settings']['fb_fan_fanbox_id'] = array(
    '#type' => 'hidden',
    '#required' => TRUE,
    '#default_value' => $fanbox_id,
  );
  $form['fb_fan_general_settings']['fb_fan_name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#size' => 45,
    '#maxlength' => 50,
    '#required' => TRUE,
    '#description' => t('Ex. My first fan box eng. This field is used to generate name for block.'),
    '#default_value' => $fanboxes[$fanbox_id]['fb_fan_name'],
  );
  $form['fb_fan_general_settings']['fb_fan_profile_id'] = array(
    '#title' => t('Page ID'),
    '#type' => 'textfield',
    '#size' => 45,
    '#maxlength' => 50,
    '#required' => TRUE,
    '#description' => t('Ex. 208184621292. Go to https://graph.facebook.com/YOURPAGENAME to get the id.'),
    '#default_value' => $fanboxes[$fanbox_id]['fb_fan_profile_id'],
  );
  $form['fb_fan_general_settings']['fb_fan_connections'] = array(
    '#title' => t('Connection Amount'),
    '#type' => 'textfield',
    '#size' => 45,
    '#maxlength' => 50,
    '#required' => TRUE,
    '#description' => t('Number of fans to display'),
    '#default_value' => $fanboxes[$fanbox_id]['fb_fan_connections'],
  );
  $form['fb_fan_general_settings']['fb_fan_width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#size' => 45,
    '#maxlength' => 50,
    '#required' => TRUE,
    '#description' => t('Width of the fan box'),
    '#default_value' => $fanboxes[$fanbox_id]['fb_fan_width'],
  );
  $form['fb_fan_general_settings']['fb_fan_height'] = array(
    '#title' => t('Height'),
    '#type' => 'textfield',
    '#size' => 45,
    '#maxlength' => 50,
    '#required' => TRUE,
    '#description' => t('Height of the fan box'),
    '#default_value' => $fanboxes[$fanbox_id]['fb_fan_height'],
  );
  $form['fb_fan_general_settings']['fb_fan_css_path'] = array(
    '#title' => t('CSS Path'),
    '#type' => 'textfield',
    '#size' => 45,
    '#maxlength' => 255,
    '#required' => FALSE,
    '#description' => t('Ex. http://example.com/style.css. If not set, PATH_TO_THEME/css/fb_fan.css will be used.'),
    '#default_value' => $fanboxes[$fanbox_id]['fb_fan_css_path'],
  );
  $form['fb_fan_general_settings']['fb_fan_stream'] = array(
    '#title' => t('Stream'),
    '#type' => 'checkbox',
    '#description' => t('Show postings from the Facebook page'),
    '#default_value' => $fanboxes[$fanbox_id]['fb_fan_stream'],
  );
  $form['fb_fan_general_settings']['fb_fan_logo'] = array(
    '#title' => t('Facebook Logo'),
    '#type' => 'checkbox',
    '#description' => t('Show the Facebook logo'),
    '#default_value' => $fanboxes[$fanbox_id]['fb_fan_logo'],
  );
  $form['fb_fan_general_settings']['fb_fan_header'] = array(
    '#title' => t('Facebook Header'),
    '#type' => 'checkbox',
    '#description' => t('Show the Facebook Header'),
    '#default_value' => $fanboxes[$fanbox_id]['fb_fan_header'],
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Submit callback for creating and editing fan boxes.
 */
function fb_fan_edit_fanbox_form_submit($form, &$form_state) {
  $fanboxes = variable_get('fb_fan_fanboxes', array());
  if ($form['fb_fan_general_settings']['is_edit']['#value'] == '1') {
    // Get allready existing id.
    $fanbox_id = $form['fb_fan_general_settings']['fb_fan_fanbox_id']['#value'];
  }
  else {
    // Generate new id.
    if (count($fanboxes) == 0) {
      $fanbox_id = 0;
    }
    else {
      $fanbox_id = max(array_keys($fanboxes));
      $fanbox_id++;
    }
  }

  foreach ($form['fb_fan_general_settings'] as $item) {
    if (is_array($item) && isset($item['#type']) && $item['#type'] != 'hidden') {
      $fanboxes[$fanbox_id][$item['#name']] = $item['#value'];
      print_r($fanbox_id);
    }
  }
  variable_set('fb_fan_fanboxes', $fanboxes);
  if ($form['fb_fan_general_settings']['is_edit']['#value'] == '1') {
    drupal_set_message(t('Fanbox changed.'));
  }
  else {
    drupal_set_message(t('Fanbox added.'));
  }
  drupal_goto(FB_PATH_ADMIN . '/fb_fan/list');
}

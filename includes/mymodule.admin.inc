<?php

/**
 * @file
 * Configuration page for mymodule.
 */

/**
 * Form builder.
 */
function mymodule_settings_form($form, &$form_state) {
  ctools_include('export');
  $data = ctools_export_load_object('mymodule', 'all');

  $languages = language_list();
  foreach ($languages as $language) {
    if ($language->enabled) {
      $form[$language->language] = array(
        '#title' => t('Contact person') . ' (' . $language->name . ')',
        '#type' => 'fieldset',
        '#tree' => TRUE
      );
      $form[$language->language]['language'] = array(
        '#type' => 'value',
        '#value' => $language->language,
      );
      $form[$language->language]['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#required' => TRUE
      );
      $form[$language->language]['email'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#required' => TRUE,
        '#element_validate' => array('_mymodule_email_validate'),
      );
      $form[$language->language]['address'] = array(
        '#type' => 'textfield',
        '#title' => t('Address'),
        '#required' => TRUE,
        '#element_validate' => array('_mymodule_address_validate'),
      );
      $form[$language->language]['country'] = array(
        '#type' => 'select',
        '#title' => t('Country'),
        '#options' => countries_get_countries('name', array('enabled' => COUNTRIES_ENABLED)),
        '#required' => TRUE,
      );

      if (isset($data[$language->language])) {
        $form[$language->language]['name']['#default_value'] = $data[$language->language]->name;
        $form[$language->language]['email']['#default_value'] = $data[$language->language]->email;
        $form[$language->language]['address']['#default_value'] = $data[$language->language]->address;
        $form[$language->language]['country']['#default_value'] = $data[$language->language]->country;
      }
    }
  }

  // copy from system_settings_form();
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }
  return $form;
}

/**
 * Form submit handler.
 */
function mymodule_settings_form_submit($form, &$form_state) {
  ctools_include('export');
  $values = $form_state['values'];
  foreach ($values as $value) {
    if (is_array($value)) {
      $objects = ctools_export_load_object('mymodule', 'conditions', array('language' => $value['language']));
      if(isset($objects[$value['language']]))
      {
        $obj = $objects[$value['language']];
      } else {
        $obj = ctools_export_new_object('mymodule');
        $obj->language = $value['language'];
      }
      $obj->name = $value['name'];
      $obj->email = $value['email'];
      $obj->address = $value['address'];
      $obj->country = $value['country'];
      ctools_export_crud_save('mymodule', $obj);
      ctools_export_load_object_reset('mymodule');
    }
  }
}

/**
 * Validator handler for email.
 */
function _mymodule_email_validate($element, &$form_state, $form) {
  if (!filter_var($element['#value'], FILTER_VALIDATE_EMAIL)) {
    form_error($element, t('Please input valid email.'));
  }
}

/**
 * Validator handler for address.
 */
function _mymodule_address_validate($element, &$form_state, $form) {
  if (strlen(trim($element['#value'])) < 21) {
    form_error($element, t('Please input full address.'));
  }
}

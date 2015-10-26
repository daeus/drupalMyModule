<?php

/**
 * @file
 * Provide default data.
 */

/**
 * Implements hook_default_mymodule().
 */
function mymodule_default_mymodule() {
  $export = array();

  $preset = new stdClass;
  $preset->api_version = 1;
  $preset->language = 'en-gb';
  $preset->name = '';
  $preset->email = '';
  $preset->address = '';
  $preset->country = 'GB';
  $export['en-gb_contact_preset'] = $preset;

  $preset = new stdClass;
  $preset->api_version = 1;
  $preset->language = 'fr';
  $preset->name = '';
  $preset->email = '';
  $preset->address = '';
  $preset->country = 'FR';
  $export['fr_contact_preset'] = $preset;

  $preset = new stdClass;
  $preset->api_version = 1;
  $preset->language = 'de';
  $preset->name = '';
  $preset->email = '';
  $preset->address = '';
  $preset->country = 'DE';
  $export['de_contact_preset'] = $preset;

  return $export;
}


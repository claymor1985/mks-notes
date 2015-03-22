<?php
/**
 * @file
 * wmc_features_ct_campus.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wmc_features_ct_campus_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function wmc_features_ct_campus_node_info() {
  $items = array(
    'campus' => array(
      'name' => t('Campus'),
      'base' => 'node_content',
      'description' => t('Holds location information mainly for campuses.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

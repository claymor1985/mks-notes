<?php
/**
 * @file
 * wmc_features_voc_attendance_mode.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function wmc_features_voc_attendance_mode_taxonomy_default_vocabularies() {
  return array(
    'attendance_mode' => array(
      'name' => 'Attendance mode',
      'machine_name' => 'attendance_mode',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}

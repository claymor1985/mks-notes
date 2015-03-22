<?php
/**
 * @file
 * wmc_features_voc_subjects.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function wmc_features_voc_subjects_taxonomy_default_vocabularies() {
  return array(
    'subjects' => array(
      'name' => 'Subjects',
      'machine_name' => 'subjects',
      'description' => 'Courses subjects imported from SITS',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}

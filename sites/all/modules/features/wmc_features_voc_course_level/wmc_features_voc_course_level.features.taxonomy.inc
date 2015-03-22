<?php
/**
 * @file
 * wmc_features_voc_course_level.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function wmc_features_voc_course_level_taxonomy_default_vocabularies() {
  return array(
    'course_level' => array(
      'name' => 'Course level',
      'machine_name' => 'course_level',
      'description' => 'Used for facet and View. For instance Undergraduate, UG with foundation etc.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}

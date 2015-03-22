<?php
/**
 * @file
 * Declares our migrations.
 */

/**
 * Implements hook_migrate_api().
 */
function wmc_import_tests_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'wmc_subjects_import_tests' => array(
        'title' => t('Westminster courses subjects import TEST'),
      ),
      'wmc_courses_import_tests' => array(
        'title' => t('Westminster courses import TEST'),
      ),
      'wmc_courses_import_tests_clear' => array(
        'title' => t('Westminster courses import CL mode'),
      ),
    ),
    'migrations' => array(
      'ImportWmcTestSubject' => array(
        'class_name' => 'ImportWmcTestSubjectMigration',
        'group_name' => 'wmc_subjects_import_tests',
      ),
      'ImportWmcTestCoursesUG' => array(
        'class_name' => 'ImportWmcTestCoursesUGMigration',
        'group_name' => 'wmc_courses_import_tests',
      ),
      'ImportWmcTestCoursesUGData' => array(
        'class_name' => 'ImportWmcTestCoursesUGDataMigration',
        'group_name' => 'wmc_courses_import_tests',
      ),
      'ImportWmcTestCoursesFC' => array(
        'class_name' => 'ImportWmcTestCoursesFCMigration',
        'group_name' => 'wmc_courses_import_tests',
      ),
      'ImportWmcTestCoursesFCData' => array(
        'class_name' => 'ImportWmcTestCoursesFCDataMigration',
        'group_name' => 'wmc_courses_import_tests',
      ),
      'ImportWmcTestCoursesPG' => array(
        'class_name' => 'ImportWmcTestCoursesPGMigration',
        'group_name' => 'wmc_courses_import_tests',
      ),
      'ImportWmcTestCoursesPGData' => array(
        'class_name' => 'ImportWmcTestCoursesPGDataMigration',
        'group_name' => 'wmc_courses_import_tests',
      ),
      'ImportWmcTestCoursesFD' => array(
        'class_name' => 'ImportWmcTestCoursesFDMigration',
        'group_name' => 'wmc_courses_import_tests',
      ),
      'ImportWmcTestCoursesFDData' => array(
        'class_name' => 'ImportWmcTestCoursesFDDataMigration',
        'group_name' => 'wmc_courses_import_tests',
      ),
      'ImportWmcTestCL' => array(
        'class_name' => 'ImportWmcTestCLMigration',
        'group_name' => 'wmc_courses_import_tests_clear',
      ),
    ),
  );
  return $api;
}

<?php
/*
 * @file
 * Migrate module hooks
 */

/*
 * Implements hook_migrate_api()
 */
function tst_migrate_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'mks' => array(
        'title' => t('MKS'),
      ),
      'subj' => array(
        'title' => t('Subject'),
      ),
      'normal' => array(
        'title' => t('Normal'),
      ),
      'clear' => array(
        'title' => t('Clearing'),
      ),
    ),
    'migrations' => array(
      'MKSXmlSubj' => array(
        'class_name' => 'MKSXmlSubjMigration',
        'group_name' => 'subj',
      ),
      'MKSXmlUG' => array(
        'class_name' => 'MKSXmlUGMigration',
        'group_name' => 'normal',
      ),
      'MKSXmlPG' => array(
        'class_name' => 'MKSXmlPGMigration',
        'group_name' => 'normal',
      ),
      'MKSXmlFC' => array(
        'class_name' => 'MKSXmlFCMigration',
        'group_name' => 'normal',
      ),
      'MKSXmlCL' => array(
        'class_name' => 'MKSXmlCLMigration',
        'group_name' => 'clear',
      ),
      'MKSXmlUGData' => array(
        'class_name' => 'MKSXmlUGDataMigration',
        'group_name' => 'normal',
      ),
      'MKSXmlPGData' => array(
        'class_name' => 'MKSXmlPGDataMigration',
        'group_name' => 'normal',
      ),
      'MKSXmlFCData' => array(
        'class_name' => 'MKSXmlFCDataMigration',
        'group_name' => 'normal',
      ),
    ),
  );
  return $api;
}
?>
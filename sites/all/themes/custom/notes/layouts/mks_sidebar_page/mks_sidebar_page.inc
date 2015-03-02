<?php
/*
 * @file
 * Layout for panels
 */
$plugin = array(
  'title' => t('Sidebar layout'),
  'icon' => 'mks_sidebar_page.png',
  'theme' => 'mks_sidebar_page',
  'admin theme' => 'mks_sidebar_page_admin',
  'category' => t('MKS'),
  'regions' => array(
    'sidebar' => t('SIDEBAR'),
    'content' => t('CONTENT'),
  )
);
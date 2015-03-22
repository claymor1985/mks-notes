<?php
/**
 * @file
 * Preprocess entities functions
 */


function notes_preprocess_node_note__listing(&$variables){
  $node = &$variables['node'];
  $content = &$variables['content'];
  $_html = &$variables['_html'];
  $_data = &$variables['_data'];
  
  $_html['title'] = $node->title;
  $_html['message'] = drupal_render($content['field_message']);
  $_html['category'] = drupal_render($content['field_category']);
  $_html['rate'] = drupal_render($content['field_rate']);
  $_html['end_date'] = drupal_render($content['field_end_date']);
}
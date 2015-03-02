<?php

/**
 * @file
 * template.php
 */
/**
 * Preprocess node.
 */
function notes_preprocess_node(&$variables) {
  $preprocess_entity_loaded = &drupal_static('notes_preprocess_entity_loaded', FALSE);
  $node = &$variables['node'];
  $content = &$variables['content'];
  $_html = &$variables['_html'];
  $_data = &$variables['_data'];
  $_data['path_to_theme'] = path_to_theme();
  $view_mode = &$variables['view_mode'];

  // Load preprocess funtions file.
  if (!$preprocess_entity_loaded) {
    $preprocess_entity_loaded = TRUE;
    $file = path_to_theme() . '/notes.preprocess_entity.inc';
    if (is_file($file)) {
      require_once $file;
    }
  }
  // Run specific preprocess function.
  $preprocess = 'notes_preprocess_node_' . $node->type . '__' . $view_mode;
  if (function_exists($preprocess)) {
    $preprocess($variables);
  }
  // Add specific templates.
  foreach ($variables['theme_hook_suggestions'] as $theme_suggestion) {
    $variables['theme_hook_suggestions'][] = $theme_suggestion . '__' . $view_mode;
  }
}


/**
 * Theme field.
 */
function notes_field(&$variables) {
  // Prevent default field wrapping into odd divs.
  // this function MUST be present even if empty.
  //dpm($variables);
}
<?php

/**
 * @file
 * Contents of omega_preprocess_html().
 */

$vars['rdf'] = new stdClass;
if (module_exists('rdf')) {
  $vars['doctype'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML+RDFa 1.1//EN">' . "\n";
  $vars['rdf']->version = ' version="HTML+RDFa 1.1"';
  $vars['rdf']->namespaces = $vars['rdf_namespaces'];
  $vars['rdf']->profile = ' profile="' . $vars['grddl_profile'] . '"';
} 
else {
  $vars['doctype'] = '<!DOCTYPE html>' . "\n";
  $vars['rdf']->version = '';
  $vars['rdf']->namespaces = '';
  $vars['rdf']->profile = '';
}
// grid debugging
global $user, $theme_key, $theme_info;
$debug_access = FALSE;
$debug_roles = theme_get_setting('debug_grid_roles');

if (!isset($user->roles[1])) {
  // Check to see if $user has the appropriate role.
  foreach ($debug_roles as $k => $v) {
    if ($v && isset($user->roles[$k])) {
      // user has access to debug tools
      $debug_access = TRUE;
    }
  }
}

// if grid debug is ON, and user either has access by role, or is uid 1
if(theme_get_setting('debug_grid_toggle') && ($debug_access || $user->uid == 1)) {
  $debug_settings = array(
    'grid_overlay_on' => theme_get_setting('debug_grid_toggle'),
    'grid_overlay_state' => theme_get_setting('debug_grid_toggle_state'),
  );
  drupal_add_js($debug_settings, 'setting');
  drupal_add_js(drupal_get_path('theme', 'omega') . '/js/debug.js', array('weight' => 1000, 'type' => 'file'));
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/debug.css');
}

// Set site title, slogan, mission, page title & separator (unless using Page Title module)
if (!module_exists('page_title')) {
  $title = (theme_get_setting('toggle_name') ? filter_xss_admin(variable_get('site_name', '')) : '');
  $slogan = (theme_get_setting('toggle_slogan') ? filter_xss_admin(variable_get('site_slogan', '')) : '');
  $page_title = strip_tags(drupal_get_title());
  $title_separator = theme_get_setting('configurable_separator');
  if ($vars['is_front']) { // Front page title settings
    switch (theme_get_setting('front_page_title_display')) {
      case 'title_slogan':
        $vars['head_title'] = drupal_set_title($title . $title_separator . $slogan, PASS_THROUGH);
        break;
      case 'slogan_title':
        $vars['head_title'] = drupal_set_title($slogan . $title_separator . $title, PASS_THROUGH);
        break;
      case 'custom':
        if (theme_get_setting('page_title_display_custom') !== '') {
          $vars['head_title'] = drupal_set_title(t(theme_get_setting('page_title_display_custom')), PASS_THROUGH);
        }
    }
  }
  else { // Non-front page title settings
    switch (theme_get_setting('other_page_title_display')) {
      case 'ptitle_slogan':
        $vars['head_title'] = drupal_set_title($page_title . $title_separator . $slogan, PASS_THROUGH);
        break;
      case 'ptitle_stitle':
        $vars['head_title'] = drupal_set_title($page_title . $title_separator . $title, PASS_THROUGH);
        break;
      case 'ptitle_custom':
        if (theme_get_setting('other_page_title_display_custom') !== '') {
          $vars['head_title'] = drupal_set_title($page_title . $title_separator . t(theme_get_setting('other_page_title_display_custom')), PASS_THROUGH);
        }
        break;
      case 'custom':
        if (theme_get_setting('other_page_title_display_custom') !== '') {
          // make sure to wrap this in a t() or you might be sacrificing a kitten
          $vars['head_title'] = drupal_set_title(t(theme_get_setting('other_page_title_display_custom')));
        }
    }
  }
}



// enable/disable optional CSS files
if (theme_get_setting('reset_css') == '1') {
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/reset.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', -100));
}
if (theme_get_setting('text_css') == '1') {
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/text.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', -99));
}
if (theme_get_setting('regions_css') == '1') {
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/regions.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', -98));
}
if (theme_get_setting('defaults_css') == '1') {
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/defaults.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', -97));
}
if (theme_get_setting('link_css') == '1') {
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/links.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', -96));
}
if (theme_get_setting('custom_css') == '1') {
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/custom.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', -1));
}
if (theme_get_setting('table_css') == '1') {
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/tables.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', -95));
}
if (theme_get_setting('pager_css') == '1') {
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/pagers.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', -94));
}
if (theme_get_setting('form_css') == '1') {
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/forms.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', -93));
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/formalize.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', -50));
  drupal_add_js(drupal_get_path('theme', 'omega') . '/js/jquery.formalize.js');
}
if (theme_get_setting('menu_css') == '1') {
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/menus.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', -92));
}

if (module_exists('skinr')) {
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/skinr.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE, 'weight', 1));
}






// responsive grid css
if (theme_get_setting('omega_responsive_grid') == 'enabled') {
  // first, include our defaults (mobile stacked with no grid styles respected)
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/responsive-grid.css', array(
    'group' => CSS_DEFAULT, 
    'every_page' => TRUE, 
    'weight', 1,
    )
  );
  // now let's add in our sized grids
  // 720px grid (if enabled)
  if(theme_get_setting('omega_responsive_medium')) {
    drupal_add_css(drupal_get_path('theme', 'omega') . '/css/720.css', array(
      'group' => CSS_DEFAULT, 
      'every_page' => TRUE, 
      'weight', 2,
      )
    );
  }
  if(theme_get_setting('omega_responsive_default')) {
    drupal_add_css(drupal_get_path('theme', 'omega') . '/css/960.css', array(
      'group' => CSS_DEFAULT, 
      'every_page' => TRUE, 
      'weight', 3,
      )
    );
  }
  if(theme_get_setting('omega_responsive_large')) {
    drupal_add_css(drupal_get_path('theme', 'omega') . '/css/1200.css', array(
      'group' => CSS_DEFAULT, 
      'every_page' => TRUE, 
      'weight', 4,
      )
    );
  }
  // Attempt to push back in 960.css for IE < 9 (which all don't support media queries)
  // this is a must have or all IE browsers < 9 will be given the mobile version
  // instead, we'll just revert to giving them the default 960gs
  drupal_add_css(drupal_get_path('theme', 'omega') . '/css/960-base.css', array(
    'browsers' => array(
      'IE' => 'lt IE 9', 
      '!IE' => FALSE
    ), 
    'group' => CSS_DEFAULT, 
    'every_page' => TRUE, 
    'weight', 100,
    )
  );
  // turn off the android zoom/scale options since we render a mobile version
  $responsive_viewport = theme_get_setting('omega_customize_viewport') ? theme_get_setting('omega_customize_viewport') : 'on';
  if(theme_get_setting('omega_customize_viewport') == 'on') {
    $initial_scale = theme_get_setting('omega_viewport_initial_scale') ? theme_get_setting('omega_viewport_initial_scale') : '1.0';
    $min_scale = theme_get_setting('omega_viewport_min_scale') ? theme_get_setting('omega_viewport_min_scale') : '1.0';
    $max_scale = theme_get_setting('omega_viewport_max_scale') ? theme_get_setting('omega_viewport_max_scale') : '1.0';
    $user_scale = theme_get_setting('omega_viewport_user_scale') ? '1' : '0';
    $meta_viewport = array(
      '#tag' => 'meta', 
      '#attributes' => array(
        'name' => 'viewport',
        'content' => 'width=device-width; initial-scale='.$initial_scale.'; maximum-scale='.$max_scale.'; minimum-scale='.$min_scale.'; user-scalable='.$user_scale.';',
      ),
    );
    drupal_add_html_head($meta_viewport, 'omega_viewport');
  }
}
// default fixed/fluid 960gs
else {
  if(theme_get_setting('omega_fixed_fluid') == 'fixed') {
    drupal_add_css(drupal_get_path('theme', 'omega') . '/css/960-base.css', array(
      'group' => CSS_DEFAULT, 
      'every_page' => TRUE, 
      'weight', 100,
      )
    );
  }
  else {
    drupal_add_css(drupal_get_path('theme', 'omega') . '/css/960-fluid.css', array(
      'group' => CSS_DEFAULT, 
      'every_page' => TRUE, 
      'weight', 100,
      )
    );
    drupal_add_js(array('fluid_grid' => theme_get_setting('omega_fixed_fluid')), 'setting');
  }
}

$vars['styles']  = drupal_get_css();
$vars['scripts'] = drupal_get_js();
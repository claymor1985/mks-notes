<div class="large-4 small-6 columns">
  <div class="panel">
    <div class="panel-heading">
      <h5 class="panel-title note-title note-rate-<?php print lcfirst($_html['rate']);?>"><?php print $_html['title'];?></h5>
    </div>
    <div class="panel-body note-body">
      <?php print $_html['message'];?>
    </div>
    <ul class="pricing-table" data-equalizer-watch>
      <li class="list-group-item note-item"><h6 class="subheader"><?php print $_html['end_date'];?></h6></li>
      <li class="list-group-item note-item"><h6 class="subheader"><?php print t('Category');?></h6> <?php print $_html['category'];?></li>
      <li class="cta-button"><a href="#" class="button">Details</a></li>
    </ul>  
  </div>
</div>

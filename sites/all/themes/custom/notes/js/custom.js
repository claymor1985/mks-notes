	/* 
	 * To change this license header, choose License Headers in Project Properties.
	 * To change this template file, choose Tools | Templates
	 * and open the template in the editor.
	 */
	
(function($){
  Drupal.behaviors.MksNotesScrolling = {
    attach: function (context, settings) {
			$(document).on("scroll", function(e){
				var scrollTop = window.pageYOffset || document.documentElement.scrollTop;
				var scrollHeight = document.documentElement.scrollHeight;
				var clientHeight = document.documentElement.clientHeight;
				if (scrollTop == scrollHeight-clientHeight) {
					$('.pager-next a').click();
				}
			});
		}
	}
})(jQuery);

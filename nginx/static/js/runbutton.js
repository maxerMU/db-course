/* eslint-disable */
!function () {
  var runData = document.getElementById('public-run-button-embed'),
    buttonUrl = runData.dataset.buttonUrl,
    webHost = runData.dataset.webHost;

  (function (p,o,s,t,m,a,n) {
    !p[s] && (p[s] = function () { (p[t] || (p[t] = [])).push(arguments); });
    !o.getElementById(s+t) && o.getElementsByTagName("head")[0].appendChild((
      (n = o.createElement("script")),
      (n.id = s+t), (n.async = 1), (n.src = m), n
    ));
  }(window, document, "_pm", "PostmanRunObject", buttonUrl));

  _pm('_property.set', 'url_root.chrome', webHost);
  _pm('_property.set', 'enableArtemis', true);
}();


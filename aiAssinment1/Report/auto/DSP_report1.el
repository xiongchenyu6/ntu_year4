(TeX-add-style-hook
 "DSP_report1"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "titlepage")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("fontenc" "T1") ("ulem" "normalem")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "inputenc"
    "fontenc"
    "graphicx"
    "grffile"
    "longtable"
    "wrapfig"
    "rotating"
    "ulem"
    "amsmath"
    "textcomp"
    "amssymb"
    "capt-of"
    "hyperref"
    "mathptmx")
   (LaTeX-add-labels
    "sec:org86ca508"
    "sec:org8d487b3"
    "fig:org83e9ed3"
    "sec:orgdb84646"
    "tab:org3955e82"
    "sec:org4d9f0cc"
    "sec:org807f460"
    "sec:orgd8df49c"
    "fig:org0f31e34"
    "fig:org01fa1fb"
    "fig:org50f9af5"
    "fig:org146612e"
    "fig:orgb9fd908"
    "fig:org2a0d4f2"
    "fig:org085161d"
    "sec:org6a89275"
    "sec:org5faee99"
    "fig:org92060a0"
    "fig:org3c5c511"
    "sec:orgd9f12fc"
    "fig:org74f4b11"
    "fig:org7951797"
    "fig:orgcbffb77"
    "fig:orgcf5dc85"
    "sec:org85caf75"))
 :latex)


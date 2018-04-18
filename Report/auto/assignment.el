(TeX-add-style-hook
 "assignment"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("scrartcl" "setspace" "doublespace")))
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
    "scrartcl"
    "scrartcl10"
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
    "indentfirst")
   (LaTeX-add-labels
    "sec:orgf6d0c21"
    "sec:org611d34d"
    "sec:orgf0e7c24"
    "sec:org94941a1"
    "sec:orgeaa0ad0"
    "sec:org550bdc6"
    "sec:org42f2a0f"
    "sec:org6f0c2e1"
    "sec:org7073cc9"
    "sec:org35617c2"
    "sec:orgd3e6cc2"
    "sec:orgf5f5c23"
    "sec:orgd0fedc3"
    "sec:org17d1b81"
    "sec:org2189a49"))
 :latex)


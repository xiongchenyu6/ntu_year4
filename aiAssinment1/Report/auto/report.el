(TeX-add-style-hook
 "report"
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
    "hyperref")
   (LaTeX-add-labels
    "sec:org67b976b"
    "sec:org14abc6c"
    "sec:orgad3a27f"
    "sec:org16bec5a"
    "sec:org19c416d"
    "tab:org6b078ca"
    "sec:orged399f5"
    "sec:org63cf285"
    "sec:org639064b"
    "fig:org0384afb"
    "fig:orgc5d9c5e"
    "sec:org817f44f"
    "fig:org8a6db96"
    "fig:org17265bc"
    "fig:orga9f21ec"
    "fig:orga175831"
    "fig:org8a9b237"
    "fig:org8764bae"
    "sec:orge96c277"
    "sec:org47c120a"
    "sec:org8f54a82"
    "sec:org757fb9e"
    "sec:org1eec57e"
    "sec:orga01be47"
    "sec:org4aa9bc8"
    "fig:org8ffca1e"
    "sec:orgff66865"
    "fig:org7c5408f"
    "fig:orga247439"
    "fig:org7ddeccf"
    "sec:org070dd69"
    "sec:orgc2cf29b"
    "sec:org4ca5ae8"
    "sec:orgb619fba"
    "sec:orgfbad817"
    "tab:orgeb535f2"
    "sec:org077af3c"
    "sec:orgc32f6a9"
    "sec:org94dd277"
    "sec:orgb1bf04c"
    "sec:orgc02cd87"
    "sec:org30c37d2"
    "sec:orge016ed9"
    "fig:org26f721e"))
 :latex)


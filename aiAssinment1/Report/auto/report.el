(TeX-add-style-hook
 "report"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("scrartcl" "12pt")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("fontenc" "T1") ("ulem" "normalem")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "scrartcl"
    "scrartcl12"
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
    "sec:org52b434c"
    "sec:org27a8bb0"
    "sec:orgc87e144"
    "sec:orgd68c741"
    "sec:orga368f14"
    "tab:org793ea79"
    "sec:orge1da213"
    "sec:orgee16887"
    "sec:orgc5cabec"
    "fig:org606d639"
    "fig:orgedc7f17"
    "sec:org48d675d"
    "fig:orgb704847"
    "fig:org90ab7ca"
    "fig:orgbb5aa01"
    "fig:org4f8b0d1"
    "fig:org07b2067"
    "fig:orgfa04102"
    "sec:orgbb5dc66"
    "sec:org3977c02"
    "sec:orga5e19e1"
    "sec:orgaa21aa2"
    "sec:org0f08393"
    "sec:orgf98fa74"
    "sec:orgc2d442b"
    "sec:org8f13b47"
    "fig:orgce3c6df"
    "fig:orgab00620"
    "fig:org778a035"
    "sec:org396ecf0"
    "sec:orgae611ff"
    "sec:org0502608"
    "sec:org3c21cce"
    "sec:org2bd2122"
    "tab:orgcbf30eb"
    "sec:orgc5423b9"
    "sec:org18f4aa9"
    "sec:org0f15ba0"
    "sec:org1ab4282"
    "sec:org4606690"
    "sec:org91b4523"
    "sec:orge216bd9"
    "fig:orgf349192"))
 :latex)


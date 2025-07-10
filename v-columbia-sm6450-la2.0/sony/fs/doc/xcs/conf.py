# -*- coding: utf-8 -*-
#
# Sphinx documentation configuration
#

import subprocess
import sphinx_rtd_theme
import os

# Basic configuration
project = 'Xperia Custom Software documentation'
copyright = '2018, Sony Mobile Communications Inc.'
release = subprocess.check_output(['git', 'describe', '--tags',
                                   '--dirty', '--always'])

extensions = ['sphinxcontrib.plantuml', 'sphinx.ext.pngmath']

master_doc = 'index'
numfig = True

# LaTeX output configuration
latex_documents = [
    ('index', 'XCS.tex', 'Xperia Custom Software',
     'Sony Mobile Communications', 'howto', True),
    (master_doc, 'allinone.tex', 'FCS',
     'Security & Enterprise', 'manual', True),
]


latex_elements = {
    'sphinxsetup': 'verbatimwithframe=false,VerbatimColor={rgb}{0.95,0.95,0.95}'
}

# HTML output configuration
html_theme = "sphinx_rtd_theme"
html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]
templates_path = ['_sphinx_rtd_theme_templates']

# PlantUML extension
plantuml_latex_output_format = 'pdf'

latex_elements = {
'figure_align': 'H'
}


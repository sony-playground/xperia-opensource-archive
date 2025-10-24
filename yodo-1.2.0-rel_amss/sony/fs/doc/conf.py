# -*- coding: utf-8 -*-
#
# Sphinx documentation configuration
#

import subprocess
import sphinx_rtd_theme
import os

# Basic configuration
project = 'Flash Core Security documentation'
copyright = '2017, Sony Mobile Communications Inc.'
release = subprocess.check_output(['git', 'describe', '--tags',
                                   '--dirty', '--always'])

extensions = ['sphinxcontrib.plantuml', 'sphinx.ext.imgmath', 'sphinx.ext.graphviz']

master_doc = 'index'
numfig = True

# LaTeX output configuration
latex_documents = [
    ('aws_iot/index', 'aws_iot.tex', 'AWS IOT',
     'Sony Mobile Communications', 'howto', True),
    ('boot/design/index', 'xboot-lib.tex', 'XBoot Library Integration',
     'Flash Security', 'manual', True),
    ('dependencies/index', 'dependencies.tex', 'Boot and Loader Dependencies',
     'Flash Security', 'manual', True),
    ('design/index', 'features.tex', 'Implementation design',
     'Flash Security', 'manual', True),
    ('fastboot_protocol/index', 'fastboot_protocol.tex', 'Fastboot protocol',
     'Flash Security', 'manual', True),
    ('firehose/index', 'firehose.tex', 'Firehose protocol',
     'Flash Security', 'manual', True),
    ('da/index', 'da.tex', 'Download agent',
     'Flash Security', 'manual', True),
    ('integration/index', 'integration.tex', 'Integration of FCS functionality',
     'Flash Security', 'manual', True),
    ('process/index', 'process.tex', 'Branching Strategy',
     'Flash Security', 'manual', True),
    ('projects/index', 'projects.tex', 'Project specific notes',
     'Flash Security', 'manual', True),
    ('requirements/index', 'requirements.tex', 'Boot and Loader Requirements',
     'Flash Security', 'manual', True),
    ('test/boot/description/index', 'xbtest.tex', 'XBoot Test Framework',
     'Flash Security', 'manual', True),
    ('test/modem/description/index', 'xmtest.tex', 'XModem Test Framework',
     'Flash Security', 'manual', True),
    ('test/xfl/robot/index', 'xfltest.tex', 'XFL Test Framework',
     'Flash Security', 'manual', True),
    ('references', 'references.tex', 'References',
     'Flash Security', 'manual', True),
    (master_doc, 'allinone.tex', 'FCS',
     'Flash Security', 'manual', True),
]

exclude_patterns = ['xcs/*']

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

if os.environ.has_key("FCS_DOC_VERSION"):
    version = os.environ.get("FCS_DOC_VERSION")
else:
    version = release

if os.environ.has_key("FCS_BUILD_MPLUS"):
    fcs_doc_branches = ['master', 'yoshino', 'nile', 'tama']
    html_context = {
        'branches' : fcs_doc_branches,
        'fcs_url_root' : "http://sandbox-fcs.mplus.sonyericsson.net/files/fcs/"
    }

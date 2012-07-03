#!/usr/bin/python3

top = '.'
out = 'build'

import os

def options(opt):
    opt.load('compiler_cxx')

def configure(cfg):
    cfg.find_program('dot', var='DOT')
    cfg.find_program('convert', var='CONVERT')
    cfg.find_program("sphinx-build2", var="SPHINXBUILD")
    cfg.find_program("doxygen", var="DOXYGEN")
    cfg.load('compiler_cxx')

def get_all_files_from_dir(dirname):
    result = []
    import os
    for root, dirs, files in os.walk(dirname):
        for filename in files:
            result.append(os.path.join(root, filename))
    return result

def build_doc(bld):
    kDoxygenPath = os.path.join(out, 'doxygen.log')
    doxygen = bld(
            rule = "${DOXYGEN} && date >> " + kDoxygenPath,
            cwd = os.getcwd(),
            source = ["Doxyfile"] + get_all_files_from_dir('sbl'),
            target = 'doxygen.log',
            name = 'doxygen'
            )


    kDocumentPath = 'doc'
    path = {
            'doctrees': os.path.join(out, 'doctrees'),
            'doc': kDocumentPath,
            'html': os.path.join(out, kDocumentPath, 'html')
            }
    cmdRemoveDoctrees = "rm -rf {}".format(path['doctrees'])
    cmdSphinxBuild = "${{SPHINXBUILD}} -b html -d {doctrees} {doc} {html}".format(**path)
    bld(
        rule   = cmdRemoveDoctrees + " && " + cmdSphinxBuild,
        cwd    = bld.path.abspath(),
        source = ['doxygen.log']
                 + bld.path.ant_glob(os.path.join(kDocumentPath, '*.py'))
                 + bld.path.ant_glob(os.path.join(kDocumentPath, '*.rst'))
                 + bld.path.ant_glob(os.path.join(kDocumentPath, '**', '*.rst')),
        target = bld.path.find_or_declare('doc/html/index.html'),
        name   = 'html',
    )

def unittest(bld):
    bld.read_shlib('gtest')
    bld.program(
            source='unittest/main.cpp',
            target='all_tests',
            use='gtest',
            )
    bld(
            rule="./${SRC}",
            source='all_tests',
            name='unittest',
            )

def build(bld):
    build_doc(bld)
    bld.add_group()
    unittest(bld)

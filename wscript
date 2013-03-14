#!/usr/bin/python3

top = '.'
out = 'build'

import os

def options(opt):
    opt.load('compiler_cxx waf_unit_test')
    opt.add_option("--doc", 
            action="store_true", 
            default=False, 
            help="Building documentation"
    )

def configure(cfg):
    cfg.find_program('dot', var='DOT')
    cfg.find_program('convert', var='CONVERT')
    cfg.find_program("sphinx-build2", var="SPHINXBUILD")
    cfg.find_program("doxygen", var="DOXYGEN")
    cfg.load('compiler_cxx waf_unit_test')

def get_all_files_from_dir(dirname):
    result = []
    import os
    for root, dirs, files in os.walk(dirname):
        for filename in files:
            if os.path.splitext(filename)[1] in {".c", ".cpp"}:
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

class UpdateUnitest:

    def __init__(self, filename, target):
        self.filename = filename
        self.target = target

    def update_unittest_main(self, bld):
        '''Automatically generate unit test main.cpp'''
        code = r'''
        #include<gtest/gtest.h>
        #include<sbl/debug.hpp>
        #include<{}>
        int main(int argv, char **argc) {{
            testing::InitGoogleTest(&argv, argc);
            return RUN_ALL_TESTS();
        }}
        '''.format(self.filename)
        with open('build/' + self.target, 'w') as maincpp:
            maincpp.write(code)
        return bld.exec_command("true")

def unittest(bld):

    bld.read_shlib('gtest')
    for i in get_all_files_from_dir('unittest'):
        u = UpdateUnitest(i, i+'.test.cpp')
        bld(
            rule=u.update_unittest_main,
            source=i,
            target=i+'.test.cpp',
        )
        bld.program(
            features='test',
            source=i+'.test.cpp',
            target=i+'.test',
            includes='.',
            cxxflags=['-Wall', '-Werror'],
            use='gtest',
        )

    from waflib.Tools import waf_unit_test
    bld.add_post_fun(waf_unit_test.summary)

def build(bld):

    if bld.options.doc:
        build_doc(bld)

    bld.add_group()
    unittest(bld)

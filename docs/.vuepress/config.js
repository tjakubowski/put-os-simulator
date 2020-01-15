const glob = require('glob');

const files = glob.sync('docs/**/*.md').map(f => '/' + f); 

module.exports = {
    title: 'OS Simulator docs',
    description: 'Univeristy project docs',
    host: 'localhost',
    base: '/put-os-simulator/',
    themeConfig: {
        nav: [
            { text: 'Team', link: '/team' },
            { text: 'Assembler editor', link: 'http://tymon.ovh/os/' },
            { text: 'GitHub', link: 'https://github.com/tjakubowski/put-os-simulator' },
        ],
        sidebar: {
            '/': [
                {
                    title: 'Documentation',
                    collapsable: false,
                    children: files
                }
            ]
        }
    },
    plugins: ['vuepress-plugin-nprogress', 'vuepress-plugin-smooth-scroll'],
}
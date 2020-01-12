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
                    children: [
                        '/docs/process',
                        '/docs/process-manager',
                    ]
                }
            ]
        }
    }
}
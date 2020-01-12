# :computer: OS Simulator docs
## Contributing to the documentation
1. Add your own class/module `.md` file in `docs` directory
2. Put added file name in `.vuepress/config.js` below `children` property.

    Example with `process.md` and `process-manager.md` files

    ```js
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
    ```
3. `git commit` & `git push`
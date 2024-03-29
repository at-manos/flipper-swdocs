// @ts-check
// Note: type annotations allow type checking and IDEs autocompletion

const lightCodeTheme = require('prism-react-renderer/themes/github');
const darkCodeTheme = require('prism-react-renderer/themes/dracula');

/** @type {import('@docusaurus/types').Config} */
const config = {
  title: "atmanos' flipper software docs",
  tagline: 'because someone needs to!',
  url: 'https://flipper.atmanos.com',
  baseUrl: '/',
  onBrokenLinks: 'throw',
  onBrokenMarkdownLinks: 'warn',
  favicon: 'img/favicon.ico',

  // GitHub pages deployment config.
  // If you aren't using GitHub pages, you don't need these.
  organizationName: 'at-manos', // Usually your GitHub org/user name.
  projectName: 'flipper-swdocs', // Usually your repo name.

  // Even if you don't use internalization, you can use this field to set useful
  // metadata like html lang. For example, if your site is Chinese, you may want
  // to replace "en" with "zh-Hans".
  i18n: {
    defaultLocale: 'en',
    locales: ['en'],
  },

  presets: [
    [
      'classic',
      /** @type {import('@docusaurus/preset-classic').Options} */
      ({
        docs: {
          sidebarPath: require.resolve('./sidebars.js'),
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            'https://github.com/at-manos/flipper-swdocs/edit/main',
        },
        blog: {
          feedOptions:{ 
            type: 'all'
          },
          showReadingTime: true,
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            'https://github.com/at-manos/flipper-swdocs/edit/main',
        },
        theme: {
          customCss: require.resolve('./src/css/custom.css'),
        },
      }),
    ],
    
  ],
  plugins: [
    [
      '@docusaurus/plugin-content-docs',
      {
        id: 'info-center',
        path: 'info-center',
        routeBasePath: 'info-center',
        sidebarPath: require.resolve('./sidebars.js'),
        // ... other options
      },
    ],
  ],

  themeConfig:
    
    /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
    ({
      colorMode: {
        defaultMode: 'dark',
        respectPrefersColorScheme: false,
      },
      navbar: {
        title: "AFSD",
        logo: {
          alt: 'My Site Logo',
          src: 'img/favicon.ico',
          height: 32,
          width: 32
        },
        items: [
          {
            type: 'doc',
            docId: 'overview/intro',
            position: 'left',
            label: 'Tutorial',
          },
          {to: '/info-center/overview/intro', label: 'Information Center', position: 'left'},
          {to: '/blog', label: 'Blog', position: 'left'},
          {
            href: 'https://ko-fi.com/atmanos',
            label: 'Buy me a coffee',
            position: 'right',
          },
          {
            href: 'https://github.com/at-manos/flipper-swdocs',
            label: 'GitHub',
            position: 'right',
          },
        ],
      },
      footer: {
        style: 'dark',
        links: [
          {
            title: 'Docs',
            items: [
              {
                label: 'Tutorial',
                to: '/docs/overview/intro',
              },
            ],
          },
          {
            title: 'Community',
            items: [
              {
                label: 'Discord',
                href: 'https://discord.gg/Pu78Uh6J9m',
              },
            ],
          },
          {
            title: 'More',
            items: [
              {
                label: 'Blog',
                to: '/blog',
              },
              {
                label: 'GitHub',
                href: 'https://github.com/at-manos/flipper-swdocs',
              },
            ],
          },
        ],
        copyright: `Copyright © ${new Date().getFullYear()} atmanos.`,
      },
      prism: {
        theme: darkCodeTheme,
        darkTheme: darkCodeTheme,
      },
      metadata: [{name: 'google-site-verification', content: 'eN_xlQ-S-S8kHm0qs9mj2N_hruK2J9avYkhkcd0VXMo'}]
    }),
};

module.exports = config;

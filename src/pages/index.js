import React from 'react';
import clsx from 'clsx';
import Layout from '@theme/Layout';
import Link from '@docusaurus/Link';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import styles from './index.module.css';
import HomepageFeatures from '@site/src/components/HomepageFeatures';

function HomepageHeader() {
  const {siteConfig} = useDocusaurusContext();
  return (
    <header id='mainGrad' style={ {height: '100%'}} className={clsx('hero mainGrad hero--primary', styles.heroBanner) }>
      <div className="container" >
        <h1 className="hero__title">{siteConfig.title}</h1>
        <p className="hero__subtitle">{siteConfig.tagline}</p>
        <div className={styles.buttons}>
          <Link
            className="button button--secondary button--lg"
            to="/docs/overview/intro">
            Go to docs!
          </Link>


        </div>
        <br></br>
        <div>
        <Link
            className="button button--secondary button--lg"
            to="https://discord.gg/Pu78Uh6J9m">
            Join the discord server!
          </Link>
        </div>
      </div>
    </header>
  );
}

export default function Home() {
  const {siteConfig} = useDocusaurusContext();
  return (
    <Layout
      title={`${siteConfig.title}`}
      description="Documentation for software on the Flipper Zero platform. Learn how to program applications, debug, and more through approachable tutorials and simple explanations.">
      <HomepageHeader  />
      {/* <HomepageFeatures /> */}

    </Layout>
  );
}

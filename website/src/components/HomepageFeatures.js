import React from 'react';
import clsx from 'clsx';
import styles from './HomepageFeatures.module.css';

const FeatureList = [
  {
    title: 'Open Source Ecosystem',
    Svg: require('../../static/img/undraw_docusaurus_mountain.svg').default,
    description: (
      <>
        DoBlink fully builds with SymbiFlow toolchain.
      </>
    ),
  },
  {
    title: 'Compile Fast',
    Svg: require('../../static/img/undraw_docusaurus_tree.svg').default,
    description: (
      <>
        Powered by Ray's distributed computing, DoBlink lets you compile FPGA applications in parallel,
        similar to what GNU does for conventional C/C++ compilation.
        
      </>
    ),
  },
  {
    title: 'Generate Multiple Configurations',
    Svg: require('../../static/img/undraw_docusaurus_react.svg').default,
    description: (
      <>
        Powered by Hydra, DoBlink lets you flexibly configure your design, enabling
        powerful design-space exploration.
      </>
    ),
  },
];

function Feature({Svg, title, description}) {
  return (
    <div className={clsx('col col--4')}>
      <div className="text--center">
        <Svg className={styles.featureSvg} alt={title} />
      </div>
      <div className="text--center padding-horiz--md">
        <h3>{title}</h3>
        <p>{description}</p>
      </div>
    </div>
  );
}

export default function HomepageFeatures() {
  return (
    <section className={styles.features}>
      <div className="container">
        <div className="row">
          {FeatureList.map((props, idx) => (
            <Feature key={idx} {...props} />
          ))}
        </div>
      </div>
    </section>
  );
}

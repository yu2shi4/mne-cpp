---
title: Develop
has_children: true
nav_order: 5
---
# Develop

MNE-CPP is designed as a two-layer framework. The library layer (Li) provides the core functionalities, which can be used during development and loaded by applications during runtime. The stand-alone applications, examples and tests are realized within the application layer of MNE-CPP. As a stand-alone software, MNE Scan is part of the application layer and makes use of the functionality of the library layer. We use a Clone-and-Own approach of the [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page){:target="_blank" rel="noopener"} library, which is integrated in our repository. [Qt](https://www.qt.io/){:target="_blank" rel="noopener"} provides tools for GUI creation whereas Eigen provides mathematical operations for linear algebra.

Below are some resources to get you started developing with MNE-CPP. You can also use our [documentation](https://mne-cpp.github.io/doxygen-api/index.html){:target="_blank" rel="noopener"} to guide you.

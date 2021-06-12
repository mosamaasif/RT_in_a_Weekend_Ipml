[![MIT License][license-shield]][license-url]

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Simple Path Tracer</h3>

  <p align="center">
  Implementation of CPU based Path Tracer based on Ray Tracing in a Weekend by Peter Shirley
  </p>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <ul>
        <li><a href="#how-to-run">How to Run</a></li>
        <li><a href="#output-images">Output Images</a></li>
      </ul>
    <li><a href="#license">License</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

This is an implementation of a very simple Path Tracer based on the famous book <a href="https://raytracing.github.io/books/RayTracingInOneWeekend.html">
<i>"Ray Tracing in a Weekend"</i></a>  by Peter Shirley.


### Built With

* [C++](https://en.wikipedia.org/wiki/C%2B%2B)
* [STB_IMAGE](https://github.com/nothings/stb)



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

* C++ - Google for your OS.
* [git](https://git-scm.com)

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/saeenyoda/RT_IN_A_WEEKEND_IMPL.git
   ```


<!-- USAGE EXAMPLES -->
## Usage

### How to Run
1. Open up command line or terminal and navigate to the cloned repo's directory
   ```sh
   cd "PATH-TO-DIRECTORY"
   ```
2. Run the main.cpp file (Using terminal on mac)
   ```sh
   clang++ -std=c++14 -stdlib=libc++ -I "PATH-TO-res/utils-FOLDER" -I "PATH-TO-res/vendors/stb_image-FOLDER" "PATH-TO-main.cpp" "PATH-TO-HittableList.cpp" "PATH-TO-Sphere.cpp" -o out/release/main 
   ```

***NOTE:***  
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`The instructions given above are for mac and that too using the terminal. For other OS and IDEs refer to the relevant docs.`

### Output Images
* Sample 1
  <img src="images/out_1.png">
* Sample 2
  <img src="images/out_2.png">
  
  
<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[license-shield]: https://img.shields.io/github/license/saeenyoda/Inverted_Indexing?label=license&style=for-the-badge
[license-url]: https://github.com/saeenyoda/Inverted_Indexing/blob/master/LICENSE

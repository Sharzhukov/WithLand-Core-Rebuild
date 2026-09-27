# Security Policy 🔒

## Supported Versions

| Version | Supported          |
|---------|--------------------|
| 0.1.x   | ✅ Active development |
| < 0.1   | ❌ Not supported   |

> Version `0.1.x` is under active development and has no stable release yet.
> Only the latest commit on `main` is guaranteed to receive security fixes.

## Reporting a Vulnerability

**Please do NOT open a public issue for security vulnerabilities.**

Instead, contact the maintainer directly:

- **Email:** [admin@sharzhukov.com](mailto:admin@sharzhukov.com) *(preferred)*
- **Website:** [sharzhukov.com](https://sharzhukov.com)
- **GitHub:** [@Sharzhukov](https://github.com/Sharzhukov)

Please include:

- A clear description of the vulnerability
- Steps to reproduce it
- The affected version or commit hash
- Your OS and compiler version
- Any potential fix, if known

If you wish to encrypt your report, request a PGP key in a brief initial
email **without** including the vulnerability details.

## Response Time

- **Acknowledgement:** within **48 hours**
- **Initial assessment:** within **5 business days**
- **Fix timeline:** communicated after assessment

## Disclosure Policy

- Once a fix is ready, a patch release will be published.
- The reporter will be credited in the release notes — **unless you request to stay anonymous**.
- We follow a **coordinated disclosure** model: please allow up to **90 days** before public disclosure, unless a fix is released sooner.

## Scope

This project is a **domain core library** with **no external dependencies** —
the attack surface is limited to:

- The C++ standard library
- The code in this repository

Out of scope:

- Vulnerabilities in the operating system or compiler toolchain
- Issues caused by modifying the source code locally
- Denial-of-service via pathological inputs, unless it triggers memory corruption

## Security Best Practices

- Always use the latest stable tagged release, when available.
- Build with warnings enabled and, when possible, with sanitizers (`-fsanitize=address,undefined`).
- Do **not** commit secrets, tokens, or private keys to the repository.
- Report any leaked credential to the maintainer immediately.

## Contact

- **Website:** [sharzhukov.com](https://sharzhukov.com)
- **GitHub:** [@Sharzhukov](https://github.com/Sharzhukov)
- **Email:** [admin@sharzhukov.com](mailto:admin@sharzhukov.com)
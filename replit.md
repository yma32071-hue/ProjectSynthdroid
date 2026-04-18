# Workspace

## Overview

pnpm workspace monorepo using TypeScript. Each package manages its own dependencies. The workspace also contains a standalone C++ JUCE synthesizer project at `jd800-inspired-synth/`.

## Stack

- **Monorepo tool**: pnpm workspaces
- **Node.js version**: 24
- **Package manager**: pnpm
- **TypeScript version**: 5.9
- **API framework**: Express 5
- **Database**: PostgreSQL + Drizzle ORM
- **Validation**: Zod (`zod/v4`), `drizzle-zod`
- **API codegen**: Orval (from OpenAPI spec)
- **Build**: esbuild (CJS bundle)

## Key Commands

- `pnpm run typecheck` — full typecheck across all packages
- `pnpm run build` — typecheck + build all packages
- `pnpm --filter @workspace/api-spec run codegen` — regenerate API hooks and Zod schemas from OpenAPI spec
- `pnpm --filter @workspace/db run push` — push DB schema changes (dev only)
- `pnpm --filter @workspace/api-server run dev` — run API server locally
- `cmake -S jd800-inspired-synth -B jd800-inspired-synth/build` — configure the JUCE synth project
- `cmake --build jd800-inspired-synth/build` — build the JUCE standalone app/plugin targets

## JUCE Synth Project

- `jd800-inspired-synth/` is an original 90s-style digital workstation synth inspired by hardware slider workflows.
- It avoids copied proprietary samples, factory riffs, names, or exact product cloning; demo riffs and wavetable content are original synthesis data.
- The CMake project fetches JUCE and defines both a standalone GUI app target and plugin-ready targets.

See the `pnpm-workspace` skill for workspace structure, TypeScript setup, and package details.

/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


      #include "clang_compiler.hpp"
      #include <string>

      const std::string casadi::ClangCompiler::meta_doc=
      "\n"
"Interface to the SDP solver MOSEK Warning: The solver MOSEK is not good\n"
"at handling linear equalities. There are several options if you notice\n"
"difficulties: play around with the parameter \"_penalty\" leave a gap\n"
"manually switch to another SDP Solver\n"
"\n"
"\n"
">List of available options\n"
"\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"|       Id        |      Type       |     Default     |   Description   |\n"
"+=================+=================+=================+=================+\n"
"| _loglevel       | OT_INT      | 0               | An integer that |\n"
"|                 |                 |                 | specifies how   |\n"
"|                 |                 |                 | much logging is |\n"
"|                 |                 |                 | done on stdout. |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| _penalty        | OT_DOUBLE         | 100000          | Penality        |\n"
"|                 |                 |                 | parameter       |\n"
"|                 |                 |                 | lambda. Must    |\n"
"|                 |                 |                 | exceed the      |\n"
"|                 |                 |                 | trace of Y.     |\n"
"|                 |                 |                 | This parameter  |\n"
"|                 |                 |                 | heavily         |\n"
"|                 |                 |                 | influences the  |\n"
"|                 |                 |                 | ability of MOSEK |\n"
"|                 |                 |                 | to treat linear |\n"
"|                 |                 |                 | equalities. The |\n"
"|                 |                 |                 | MOSEK standard   |\n"
"|                 |                 |                 | default (1e8)   |\n"
"|                 |                 |                 | will make a     |\n"
"|                 |                 |                 | problem with    |\n"
"|                 |                 |                 | linear equality |\n"
"|                 |                 |                 | return unusable |\n"
"|                 |                 |                 | solutions.      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| _printlevel     | OT_INT      | 1               | A printlevel of |\n"
"|                 |                 |                 | zero will       |\n"
"|                 |                 |                 | disable all     |\n"
"|                 |                 |                 | output. Another |\n"
"|                 |                 |                 | number          |\n"
"|                 |                 |                 | indicates how   |\n"
"|                 |                 |                 | often a line is |\n"
"|                 |                 |                 | printed.        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| _reuse          | OT_INT      | 4               | Maximum on the  |\n"
"|                 |                 |                 | number of times |\n"
"|                 |                 |                 | the Schur       |\n"
"|                 |                 |                 | complement      |\n"
"|                 |                 |                 | matrix is       |\n"
"|                 |                 |                 | reused          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| _rho            | OT_DOUBLE         | 4               | Potential       |\n"
"|                 |                 |                 | parameter. Must |\n"
"|                 |                 |                 | be >=1          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| _use_penalty    | OT_BOOLEAN      | true            | Modifies the    |\n"
"|                 |                 |                 | algorithm to    |\n"
"|                 |                 |                 | use a penality  |\n"
"|                 |                 |                 | gamma on r.     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| _zbar           | OT_DOUBLE         | 1.000e+10       | Initial upper   |\n"
"|                 |                 |                 | bound on the    |\n"
"|                 |                 |                 | objective of    |\n"
"|                 |                 |                 | the dual        |\n"
"|                 |                 |                 | problem.        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| dualTol         | OT_DOUBLE         | 0.000           | Tolerance for   |\n"
"|                 |                 |                 | dual            |\n"
"|                 |                 |                 | infeasibility   |\n"
"|                 |                 |                 | (translates to  |\n"
"|                 |                 |                 | primal          |\n"
"|                 |                 |                 | infeasibility   |\n"
"|                 |                 |                 | in mosek terms)  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| gapTol          | OT_DOUBLE         | 0.000           | Convergence     |\n"
"|                 |                 |                 | criterion based |\n"
"|                 |                 |                 | on distance     |\n"
"|                 |                 |                 | between primal  |\n"
"|                 |                 |                 | and dual        |\n"
"|                 |                 |                 | objective       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| inf             | OT_DOUBLE         | 1.000e+30       | Treat numbers   |\n"
"|                 |                 |                 | higher than     |\n"
"|                 |                 |                 | this as         |\n"
"|                 |                 |                 | infinity        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| maxIter         | OT_INT      | 500             | Maximum number  |\n"
"|                 |                 |                 | of iterations   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| primalTol       | OT_DOUBLE         | 0.000           | Tolerance for   |\n"
"|                 |                 |                 | primal          |\n"
"|                 |                 |                 | infeasibility   |\n"
"|                 |                 |                 | (translates to  |\n"
"|                 |                 |                 | dual            |\n"
"|                 |                 |                 | infeasibility   |\n"
"|                 |                 |                 | in mosek terms)  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| stepTol         | OT_DOUBLE         | 0.050           | Terminate the   |\n"
"|                 |                 |                 | solver if the   |\n"
"|                 |                 |                 | step length in  |\n"
"|                 |                 |                 | the primal is   |\n"
"|                 |                 |                 | below this      |\n"
"|                 |                 |                 | tolerance.      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"\n"
"\n"
">List of available stats\n"
"\n"
"+--------------------+\n"
"|         Id         |\n"
"+====================+\n"
"| solution_type      |\n"
"+--------------------+\n"
"| termination_reason |\n"
"+--------------------+\n"
"\n"
"\n"
"\n"
"\n"
;

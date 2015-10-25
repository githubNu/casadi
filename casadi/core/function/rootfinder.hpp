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


#ifndef CASADI_ROOTFINDER_HPP
#define CASADI_ROOTFINDER_HPP

#include "function_internal.hpp"
#include "linear_solver.hpp"
#include "plugin_interface.hpp"


/// \cond INTERNAL
namespace casadi {

  /// Internal class
  class CASADI_EXPORT
  Rootfinder : public FunctionInternal,
               public PluginInterface<Rootfinder> {
  public:
    /** \brief Constructor
     *
     * \param f   Function mapping from (n+1) inputs to 1 output.
     */
    Rootfinder(const std::string& name, const Function& f);

    /// Destructor
    virtual ~Rootfinder() = 0;
    ///@{
    /** \brief Number of function inputs and outputs */
    virtual size_t get_n_in() const { return f_.n_in();}
    virtual size_t get_n_out() const { return f_.n_out();}
    ///@}

    /// @{
    /** \brief Sparsities of function inputs and outputs */
    virtual Sparsity get_sparsity_in(int ind) const { return f_.sparsity_in(ind);}
    virtual Sparsity get_sparsity_out(int ind) const { return f_.sparsity_out(ind);}
    /// @}

    /// Initialize
    virtual void init();

    /** \brief  Propagate sparsity forward */
    virtual void spFwd(const bvec_t** arg, bvec_t** res, int* iw, bvec_t* w);

    /** \brief  Propagate sparsity backwards */
    virtual void spAdj(bvec_t** arg, bvec_t** res, int* iw, bvec_t* w);

    /// Is the class able to propagate seeds through the algorithm?
    virtual bool spCanEvaluate(bool fwd) { return true;}

    /// Solve the system of equations and calculate derivatives
    virtual void evaluate();

    /// Solve the nonlinear system of equations
    virtual void solveNonLinear() = 0;

    ///@{
    /** \brief Generate a function that calculates \a nfwd forward derivatives */
    virtual Function getDerForward(const std::string& name, int nfwd, Dict& opts);
    virtual int numDerForward() const { return 64;}
    ///@}

    ///@{
    /** \brief Generate a function that calculates \a nadj adjoint derivatives */
    virtual Function getDerReverse(const std::string& name, int nadj, Dict& opts);
    virtual int numDerReverse() const { return 64;}
    ///@}

    /** \brief Create call to (cached) derivative function, forward mode  */
    virtual void callForward(const std::vector<MX>& arg, const std::vector<MX>& res,
                         const std::vector<std::vector<MX> >& fseed,
                         std::vector<std::vector<MX> >& fsens,
                         bool always_inline, bool never_inline);

    /** \brief Create call to (cached) derivative function, reverse mode  */
    virtual void callReverse(const std::vector<MX>& arg, const std::vector<MX>& res,
                         const std::vector<std::vector<MX> >& aseed,
                         std::vector<std::vector<MX> >& asens,
                         bool always_inline, bool never_inline);

    /// Number of equations
    int n_;

    /// The function f(z, x1, x2, ..., xn) == 0
    Function f_;

    /// Jacobian of f with respect to z
    Function jac_;

    /// Linear solver
    LinearSolver linsol_;

    /// Factorization up-to-date?
    bool fact_up_to_date_;

    /// Constraints on decision variables
    std::vector<int> u_c_;

    /// Indices of the input and output that correspond to the actual root-finding
    int iin_, iout_;

    // Creator function for internal class
    typedef Rootfinder* (*Creator)(const std::string& name, const Function& f);

    // No static functions exposed
    struct Exposed{ };

    /// Collection of solvers
    static std::map<std::string, Plugin> solvers_;

    /// Short name
    static std::string shortname() { return "nlsol";}

    /// Infix
    static const std::string infix_;
  };



} // namespace casadi
/// \endcond

#endif // CASADI_ROOTFINDER_HPP


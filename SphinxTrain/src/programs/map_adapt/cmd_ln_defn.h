/*********************************************************************
 *
 * $Header$
 *
 * CMU ARPA Speech Project
 *
 * Copyright (c) 1998 Carnegie Mellon University.
 * All rights reserved.
 *
 *********************************************************************
 *
 * File: cmd_ln_defn.h
 * 
 * Description: 
 * 	Command line definitions for map_adapt
 *
 * Author: 
 * 	David Huggins-Daines <dhuggins@cs.cmu.edu>
 *********************************************************************/

#ifndef CMD_LN_DEFN_H
#define CMD_LN_DEFN_H
const char helpstr[] = 
"Description: \n"
"\n"
"Given a speaker-independent (or other baseline) model and a\n"
"set of forward-backward statistics collected from adaptation\n"
"data using this model as initialization, map_adapt will update\n"
"the model parameters to maximize the a posteriori probability\n"
"of the adaptation data given a prior distribution derived from\n"
"the baseline model.\n";

const char examplestr[] =
"Example: \n"
"map_adapt -mapmeanfn map_model/means -meanfn baseline/means \\\n"
"          -varfn baseline/variances -accumdir bwaccumdir\n";

    static arg_def_t defn[] = {
	{ "-help",
	  CMD_LN_BOOLEAN,
	  CMD_LN_NO_VALIDATION,
	  "no",
	  "Shows the usage of the tool"},

	{ "-example",
	  CMD_LN_BOOLEAN,
	  CMD_LN_NO_VALIDATION,
	  "no",
	  "Shows example of how to use the tool"},

	{ "-meanfn",
	  CMD_LN_STRING,
	  CMD_LN_NO_VALIDATION,
	  CMD_LN_NO_DEFAULT,
	  "Baseline (speaker-independent) Gaussian density mean file"},

	{ "-varfn",
	  CMD_LN_STRING,
	  CMD_LN_NO_VALIDATION,
	  CMD_LN_NO_DEFAULT,
	  "Baseline (speaker-independent) Gaussian density variance file"},

	{ "-tmatfn",
	  CMD_LN_STRING,
	  CMD_LN_NO_VALIDATION,
	  CMD_LN_NO_DEFAULT,
	  "Baseline (speaker-independent) transition matrix parameter file name"},

	{ "-mixwfn",
	  CMD_LN_STRING,
	  CMD_LN_NO_VALIDATION,
	  CMD_LN_NO_DEFAULT,
	  "Baseline (speaker-independent) mixture weight parameter file name"},

	{ "-accumdir",
	  CMD_LN_STRING_LIST,
	  CMD_LN_NO_VALIDATION,
	  CMD_LN_NO_DEFAULT,
	  "One or more paths containing reestimation sums from running bw on adaptation data" },

	{ "-fixedtau",
	  CMD_LN_BOOLEAN,
	  CMD_LN_NO_VALIDATION,
	  "no",
	  "Use a uniform value for the prior hyperparameter tau"},

	{ "-bayesmean",
	  CMD_LN_BOOLEAN,
	  CMD_LN_NO_VALIDATION,
	  "yes",
	  "Use simple Bayesian updating for the means, ignoring tau (recommended)."},

	{ "-tau",
	  CMD_LN_FLOAT32,
	  CMD_LN_NO_VALIDATION,
	  "10.0",
	  "The uniform value for the tau (prior weight) hyperparameter"},

	{ "-mwfloor",
	  CMD_LN_FLOAT32,
	  CMD_LN_NO_VALIDATION,
	  "0.00001",
	  "Mixing weight smoothing floor" },

	{ "-varfloor",
	  CMD_LN_FLOAT32,
	  CMD_LN_NO_VALIDATION,
	  "0.00001",
	  "Variance smoothing floor" },

	{ "-tpfloor",
	  CMD_LN_FLOAT32,
	  CMD_LN_NO_VALIDATION,
	  "0.0001",
	  "Transition probability smoothing floor" },

        { "-mapmeanfn",
          CMD_LN_STRING,
	  CMD_LN_NO_VALIDATION,
          CMD_LN_NO_DEFAULT,
          "The output MAP mean file"},

        { "-mapvarfn",
          CMD_LN_STRING,
	  CMD_LN_NO_VALIDATION,
          CMD_LN_NO_DEFAULT,
          "The output MAP var file"},

        { "-mapmixwfn",
          CMD_LN_STRING,
	  CMD_LN_NO_VALIDATION,
          CMD_LN_NO_DEFAULT,
          "The output MAP mixture weight file"},

        { "-maptmatfn",
          CMD_LN_STRING,
	  CMD_LN_NO_VALIDATION,
          CMD_LN_NO_DEFAULT,
          "The output MAP transition matrix file"},

	{ NULL, CMD_LN_UNDEF, CMD_LN_NO_VALIDATION, CMD_LN_NO_DEFAULT, NULL }
    };


#endif /* CMD_LN_DEFN_H */ 


/*
 * Log record.  Maintained by RCS.
 *
 * $Log$
 * Revision 1.6  2005/07/05  17:06:40  dhdfu
 * Requires -2passvar to be OFF!  (doh)
 * 
 * Revision 1.5  2005/07/05 16:21:01  dhdfu
 * Make variance re-estimation work (requires -2passvar to be off).
 * Implement and enable transition matrix re-estimation (does basically nothing, of course).
 * Refactor the code into a bunch of smaller functions to make it less unweildy.
 *
 * Revision 1.4  2005/06/17 18:32:22  dhdfu
 * Make this work again for SCHMM.  Some steps towards fixing variance updates (it kind of works without -2passvar) but I fear we have to do it in two passes as there is no "shortcut" unlike for ML variance estimation
 *
 * Revision 1.3  2005/06/16 04:31:28  dhdfu
 * Replace this program with my own "map_update" code.  This implements
 * the MAP update equations from Chin-Hui Lee and Jean-Juc Gauvain's
 * papers in addition to the (actually superior) simple interpolation
 * from Sam-Joo's code (which is still the default).  There is no longer
 * any need to run norm to generate an ML estimate, we do that
 * internally.  Also we can now adapt mixture weights, which may or may
 * not improve accuracy slightly versus only updating the means.
 *
 * Currently this is BROKEN for semi-continuous models (the old map_adapt
 * worked fine for them but didn't do a whole lot since it couldn't
 * update mixture weights).  But it shouldn't be hard to fix it.  Also,
 * variance updating doesn't work, and transition matrix updating isn't
 * implemented.  These might require some changes to bw.
 *
 *
 */

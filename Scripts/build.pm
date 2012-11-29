#!/usr/bin/perl -w

package build;

use strict;
use warnings;

use Exporter;
use base 'Exporter';    # or: our @ISA = 'Exporter';

our @EXPORT = qw( $test );

our $test = 42;

1;


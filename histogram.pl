#!/usr/bin/perl

# Time-stamp: <2005-07-23 17:10:50 kasper>


# TODO:

# Der er noget med de sidste punkter der ikke bliver printet
# rigtigt med float:
# Der er noget med --col 1,2 --plot der ikke er rigtigt. Binsne er flyttet en tak opad..

use warnings;
use strict;
use Getopt::Long;
use POSIX;
use constant USAGE =><<END;

SYNOPSIS:

 histogram.pl [OPTIONS] [infile [outfile]]

DESCRIPTION:

Makes a 2D or 3D histogram data-set for gnuplot from data in specified
column(s) of an input file. Lines not starting with a real number are
ignored. It also understands "framed" tables dumped from databases.

OPTIONS:

       --help
             Prints this help.
       --[no]onlyreal
             Ignore lines not starting with alpha chars. This is
             default. By specifying --noonlyreal only lines starting
             with '#' are ignored
       --column <int>[,<int>]
             Column number to use (starts at 1). Default is 1. If two
             comma seperated numbers are given 3d histogram output is
             printed (the format that splot in gnuplot takes.)
       --binsize|--xbinsize <float>
             Bin size. Bin size for the x-column in 3D histograms.
       --plot
             Invokes gnuplot and shows a quick and dirty plot. The
             generated plot gets saved as tmp.gp.
       --save <basename>
             Same as --plot but saves a gnuplot file and a eps file
             with the specified basename.
       --logz <float>
             Use with --plot to get log base <float> z-axis
       --logy <float>
             Use with --plot to get log base <float> y-axis
       --logx <float>
             Use with --plot to get log base <float> x-axis
       --contour
             Prints contour points at the borders of the bins to
             produce a contour line in gnuplot.
       --[no]centerbin
             Whether the x value of 2D plots represent the center
             (default) or the beginning of the bin.
       --nulledge
             Used with 3D histograms it just adds a leftmost column and
             a bottom row of zeros. It still report the center of the
             bins. This is handy for making 3D histograms (and 2D
             color sheets).
       --cdf
             Makes a Cumulative Distribution Function. (THIS IS BETA FOR 3D)
       --smooth <float>
             Used with 2D histograms. Starts with specified binsize
             finds a one equal to or larger that gives a less squiggly
             histogram. The option argument has to be 0 or larger and
             specifies how strong the smoothening has to be. 2 is
             recomended.
       --ybinsize <float>
             Bin size for the y-column in 3D histograms. Defaults to
             value of xbinsize.
       --normalise
             Normalise.
       --cumulative
             Cumulative histogram. (in y-direction in case of 3D
             histogram).
       --reverse
             Reverse cumulative histogram. (in y-direction in case of
             3D histogram).
       --averagebin
             Used with 2D histograms to average binsize if --binsize is
             0 or unspecified.
       --float
             Used with 2D histograms to give floating bins (Implies
             normalise and contour)
       --firstx <float>
             Used with 2D and 3D histograms to specify the lowest
             x-value to be considered.
       --lastx <float>
             Used with 2D and 3D histograms to specify the highest
             x-value to be considered. NOTE: The script will adjust
             this value to match a bin border
       --xrange [firstx]:[lastx]
             Convenience option to specify first and last x-value specified.
       --firsty <float>
             Used with 3D histograms to make the center of the first y-bin at
             least <float>.
       --lasty <float>
             Used with 3D histograms to make the center of the last y-bin at
             least <float>.
       --yrange [firstx]:[lastx]
             Convenience option to specify first and last y-value specified.
       --xbins <int>
             Used with 2D or 3D histograms to make the the number of x-bins
             at least <int> directions).
       --ybins <int>
             Used with 3D histograms to make the the number of y-bins
             at least <int> directions).
       --squarematrix
             Used with 3D histograms to make the geneneated data
             matrix squareshaped (same number of bins in both
             directions).
       --diffnull
             Used with 3D histograms substract the nullmodel of
             independent cols. That is to get P(A,B)-P(A)P(B).

EXAMPLES:

 # Make a histogram of one column:
 histogram.pl -bin 10 -col 2 file.tbl 2d.hist

 # Two columns:
 cat file.tbl | histogram.pl -bin 100 -col 3,4 > 3d.hist

AUTHOR:

Anders Krogh / Kasper Munch

COPYRIGHT:

This program is free software. You may copy and redistribute it under
the same terms as Perl itself.

END

my $help = 0;
my $smooth = 0;
my $onlyreal = 1;
my $column = 1;
my $xbinsize = 0;
my $ybinsize = 0;
my $start = 0;
my $normalise = 0;
my $float = 0;
my $averagebin = 20;
my $cdf = 0;
my $contour = 0;
my $cumulative = 0;
my $reverse = 0;
my $squarematrix = 0;
my $xbins = 0;
my $ybins = 0;
my $lasty = undef;
my $firsty = undef;
my $lastx = undef;
my $firstx = undef;
my $save = '';
my $xrange = '';
my $yrange = '';
my $diffnull = 0;
my $nulledge = 0;
my $plot = 0;
my $logz = 0;
my $logy = 0;
my $logx = 0;

my $centerbin = 1;

GetOptions(
           "help" => \$help,
           "centerbin!" => \$centerbin,
           "onlyreal!" => \$onlyreal,
           "binsize|xbinsize=f" => \$xbinsize,
           "ybinsize=f" => \$ybinsize,
           "start=f" => \$start,
           "smooth=f" => \$smooth,
           "normalise" => \$normalise,
           "float" => \$float,
           "contour" => \$contour,
           "cumulative" => \$cumulative,
           "cdf" => \$cdf,
           "reverse" => \$reverse,
           "averagebin|avbin=f" => \$averagebin,
           "column|columns=s" => \$column,
           "squarematrix|equallength" => \$squarematrix,
           "xbins=i" => \$xbins,
           "ybins=i" => \$ybins,
           "lasty=f" => \$lasty,
           "firsty=f" => \$firsty,
           "lastx=f" => \$lastx,
           "firstx=f" => \$firstx,
           "save=s" => \$save,
           "xrange=s" => \$xrange,
           "yrange=s" => \$yrange,
           "diffnull" => \$diffnull,
           "nulledge" => \$nulledge,
           "plot|qd|quickanddirty" => \$plot,
           "logz=f" => \$logz,
           "logx=f" => \$logx,
           "logy=f" => \$logy,
          ) or die $!, USAGE;

$help and die USAGE;

#warn "\n=====================================\n NB: THIS SCRIPT HAS TO BE TESTED!\n=====================================\n\n";

my @C = ();
if ($column =~ /,/) {
  @C = split /,/, $column;
} else {
  @C = ($column);
}

@C > 2 and die "You can't specify more than two columns.\n";
# Substract one from each to get the column indices:
@C = map { --$_ } @C;

# Incompatible options:
@C == 1 && ($squarematrix || $lasty || $firsty || $ybins || $nulledge)
  and die "Incompatible options: --nulledge, --firsty, --lasty, and --squarematrix are only for use with 3D histograms.\n";
@C == 2 && $float 
  and die "Incompatible options: --float are for use with 2D histograms.\n";
$float && ($xbinsize || $cumulative || $reverse)
  and die "Incompatible options: --float makes --binsize, --cumulative and --reverse obsolete.\n";
$nulledge && $contour
  and die "Incompatible options: --nulledge and --contour\n";
!$centerbin and $cdf || $float || $contour
  and die "Incompatible options: Don't use --nocenterbin with --cdf, --float, or --contour\n";

# Input and output:
@ARGV = ('-') unless @ARGV;
my $input = shift @ARGV;
open my $in, "$input" or die "$input: $!\n";
if (!@ARGV) {
  @ARGV = $plot || $save ? ('/tmp/tmp.tbl') : ('>&STDOUT')
}
my $output = shift @ARGV;
open my $out, ">$output" or die "$output: $!\n";

# Real number regexp:
my $real = '(?:(?i)(?:[+-]?)(?:(?=[0123456789]|[.])(?:[0123456789]*)(?:(?:[.])(?:[0123456789]{0,}))?)(?:(?:[Ee])(?:(?:[+-]?)(?:[0123456789]+))|))';

# Get the data into an array of arrays:
my @data=();
while (<$in>) {

  # Take care of the line if it is part om a table dumped from a database;
  s/^\|\s*//g;
  s/\s*\|$//g;
  s/\s+\|\s+/\t/g;

  # Skip nonsense and comment lines:
  if ($onlyreal) {
    next unless /^$real/;
  } else {
    next if /^#/;
  }
  $_ =~ s/^\s+//;
  chomp;

  # Skip blank lines:
  next if /^\s*$/;

  my @Fld = split /\s+/, $_;
  # We don't consider lines with less than $column+1 columns:
  next if $#Fld < max(@C);

  # Check that each read entry is a real number:
  for my $c (@C) {
    $Fld[$c] =~ /^$real$/
      or die "\"$Fld[$c]\" on line $. in column $c is not a real number\n";
  }

  # Make an array of the one or two column entries we need from
  # the line:
  my @s = @Fld[@C];

  # Add it to the data array;
  push(@data,\@s);
}

@data or die "Seems there was no input data.\n";

# Sort the array by the first column listed:
@data = sort { $a->[0] <=> $b->[0] } @data;

my $N = scalar @data;

# Factor for normalization:
my $scale = 1;

# Convenience options:
if ($xrange) {
  my ($f, $l) = split /:/, $xrange;
  $firstx = $f ne '' ? $f : undef;
  $lastx = $l ne '' ? $l : undef;
}
if ($yrange) {
  my ($f, $l) = split /:/, $yrange;
  $firsty = $f ? $f : undef;
  $lasty = $l ? $l : undef;
}
if ($cdf) {
  $normalise = 1;
  $cumulative = 1;
  $scale = 1/($N**@C);
} elsif ($normalise) {
  $scale = 1/($N*$xbinsize**@C);
}

if ($smooth) {
  $smooth = 10**-$smooth;
  if ( not $normalise) {
    $smooth *= $N;
    unless ( $cumulative || $reverse) {
      $smooth *= $xbinsize;
    }
  }
}

REDO:

my @x = (); # Holding the bins.
my @h = (); # Holding the data.

if ($float) {
  # Floating bin size
  $xbinsize = $averagebin if (!$xbinsize);
  $xbinsize = int($xbinsize + 0.001);
  my $x2 = $data[0][0];
  my $n = 0;
  for (my $i=0; $i<$N; $i+=$xbinsize) {
    my $x1 = $x2;
    $x[$n] = $x1;
    my $e2 = $i+$xbinsize;
    my $e1 = $e2-1;
    if ($e2 >= $N) {
      $e1 = $e2 = $N - 1;
    }
    $x2 = ($data[$e1][0] + $data[$e2][0]) * 0.5;
    $h[$n] = ($e1+1-$i)/($N*($x2-$x1));
    ++$n;
  }
  $x[$n] = $x2;
  $h[$n] = 0;

} elsif (!$xbinsize && ($cumulative || $reverse)) {
  @x = map { $$_[0] } @data;
  my $z = 1;
  if ($normalise) {
    $z = 1 / $N;
  }
  $h[0] = $z;
  if ($reverse) {
    $h[0] = $N*$z;
    $z = -$z;
  }
  for (my $n=0; $n<$N-1; ++$n) {
    $h[$n+1] = $h[$n] + $z;
  }
} else {

  # Find the max and min of the col one:
  my ($min1, $max1) = (sort {$a->[0] <=> $b->[0]} @data)[0,$#data];
  ($min1, $max1) = ($$min1[0], $$max1[0]);

  # Establish binsize if unspecified:
  if (!$xbinsize) {
    if ($max1 - $min1) {
      $xbinsize = ($max1 - $min1) / $averagebin;
    } else {
      die "You didn't specify a binsize and all column values are equal\n";
    }
  }

  # Take into account if x-ranges are specified by options:
  if (defined $firstx && $firstx > $min1 && $firstx < $max1) {
    $min1 = $firstx;
  }
  if (defined $lastx && $lastx < $max1 && $lastx > $min1) {
    $max1 = $lastx;
  }

  # Find beginning of first bin in a way that makes bins align nicely
  # with zero (in case this is in the value range):
  my $x2 = $min1;
  $x2 *= -1 if $x2 < 0;
  my $rest = int($x2/$xbinsize) - $x2/$xbinsize;
  $x2 = int($x2/$xbinsize) * $xbinsize;
  $x2 = -$x2 if $min1 < 0;
  $x2 = $x2 - $xbinsize if abs($rest) > 0.000000000001;
  $x2 = sprintf("%.12f", $x2);

  # Find number of bins in each row for the first
  # column making the sub histograms:
  my $minxbins = int( ( $max1 - $x2 ) / $xbinsize) + 1;

  # Make the histogram of the first column:
  my @xh = ();
  my $skipped = 0;

  # Save value of start of first bin:
  my $firstxbin = $x2;

  # Loop over all the data points:
  for (my $bin=0, my $i=0; $i<$N; ) {
    # We only want the ones fitting in this particular bin, in case
    # we skip some of the first ones using --firstx and/or --lastx:
    if ($data[$i][0] >= $x2 and (defined $lastx ? $data[$i][0] <= $lastx : 1) ) {
      # Write start of this bin initialise data array for the bin:
      $x[$bin] = $x2;
      $h[$bin] = [];
      # Get start of next bin:
      $x2 += $xbinsize;
      # $x2 = $firstxbin + (($bin+1) * $xbinsize);
      $x2 = sprintf("%.12f", $x2);
      # Loop over points that fits in the same bin:
      while ($i < $N && $data[$i][0] < $x2) {
        push @{$h[$bin]}, $data[$i];
        ++$i;
      }
      # Increment bin number:
      $bin++;
    } else {
      # Record nr. of skipped data points:
      $skipped++;
      $i++;
      next;
    }
  }

  # Adjust scale in accordance with skipped entries:
  if (defined $firstx && $skipped) {
    $scale *= $N / ($N-$skipped);
  }

  # Fill in bins with null arrays to fit minbins:
  for (my $n=scalar(@h); $n < $minxbins + $nulledge; $n++) {
    $x[$n] = $x2;
    $h[$n] = [];
    $x2 += $xbinsize;
    $x2 = sprintf("%.12f", $x2);
  }

  if (@C == 1) {
    # If we are making 2d hist we turn the array of arrays into
    # numbers and multiply by scale:

    @h = map { scalar(@$_) * $scale } @h;

    if ($cumulative) {
      for (my $n=0; $n<$#h-$nulledge; ++$n) {
        $h[$n+1] += $h[$n];
      }
    } elsif ($reverse) {
      for (my $n=$#h-$nulledge; $n>0; --$n) {
        $h[$n-1] += $h[$n];
      }
    }
  } else {
    # We are doing 3D. So we make sub histograms of the second entries
    # in the data arrays:

    # Save the histogram of the x-column for later if we have to do
    # diffnull:
    if ($diffnull) {
      @xh = map { scalar(@$_) * $scale } @h;
    }

    my ($min2, $max2) = (sort {$a->[1] <=> $b->[1]} @data)[0,$#data];
    ($min2, $max2) = ($$min2[1], $$max2[1]);

    $ybinsize ||= $xbinsize;

    # Take into account if y-ranges are specified by options:
    if (defined $firsty && $firsty > $min2 && $firsty < $max2) {
      $min2 = $firsty;
    }
    if (defined $lasty && $lasty < $max2 && $lasty > $min2) {
      $max2 = $lasty;
    }

    # Find beginning of the sub histograms:
    $x2 = $squarematrix ? min($min1,$min2) : $min2;
    $x2 *= -1 if $x2 < 0;
    # $x2 = $ybinsize * int($x2/$ybinsize);
    # $x2 = -$x2 - $ybinsize if $squarematrix ? min($min1,$min2) : $min2 < 0;
    my $rest = int($x2/$ybinsize) - $x2/$ybinsize;
    $x2 = int($x2/$ybinsize) * $ybinsize;
    $x2 = -$x2 if $squarematrix ? min($min1,$min2) : $min2 < 0;
    $x2 = $x2 - $ybinsize if abs($rest) > 0.000000000001;
    $x2 = sprintf("%.12f", $x2);

    my $firstybin = $x2;

    # Find the span in numbers we have to consider for the second
    # column making the sub histograms:
    my $maxfigure = $squarematrix ? max($max1,$max2) : $max2;

    # Find number of bins in each row for the first
    # column making the sub histograms:
    my $minybins = int( ( $maxfigure - $x2 ) / $ybinsize) + 1;

    my @t = @h;
    @h = ();
    my @b = @x;
    @x = ();
    my @y = ();
    for (my $p=0; $p<@t; $p++) {
      @{$t[$p]} = sort { $a->[1] <=> $b->[1] } @{$t[$p]};
      my $i = 0;
      my $n = 0;
      my $x2 = $firstybin;
      my @sh = ();
      while ($i < @{$t[$p]}) {
        $y[$n] = $x2;
        $x2 += $ybinsize;
        $x2 = sprintf("%.12f", $x2);
        $sh[$n] = 0;
        while ($i < @{$t[$p]} && $t[$p][$i][1] < $x2) {
          $sh[$n] += 1;
          ++$i;
        }
        $sh[$n] *= $scale;
        ++$n;
      }
      # Make sure that all the subhistograms have the same number of
      # bins. Otherwise gnuplot can't handle it as grid data:
      while ($n < $minybins + 1) {
        $y[$n] = $x2;
        $sh[$n] = 0;
        $x2 += $ybinsize;
        $x2 = sprintf("%.12f", $x2);
        $n++;
      }

      if ($cumulative) {
        for (my $n=0; $n<$#sh-1; ++$n) {
          $sh[$n+1] += $sh[$n];
        }
      } elsif ($reverse) {
        for (my $n=$#sh-1; $n>0; --$n) {
          $sh[$n-1] += $sh[$n];
        }
      }

      # Add the subhist to the total hist array:
      push @h, \@sh;

      my @u = ();
      # Make @x hold the two bin cols:
      for (my $q=0; $q<@sh; $q++) {
        push @u, [$b[$p], $y[$q]];
      }
      push @x, \@u;
    }

    if ($squarematrix) {
      my $x2 = $firstybin + $ybinsize * (scalar(@t) - 1);
      # If the matrix is not square, we make some dummy data blocks (in
      # splot lingo).
      for (my $dbl = $minybins - scalar @t; $dbl > 0; $dbl--) {
        $x2 += $ybinsize;
        $x2 = sprintf("%.12f", $x2);

        # Make the z col:
        my @d = ();
        for (my $i=0; $i<$minybins; $i++) {
          $d[$i] = 0;
        }
        $d[$#d] .= "\n" unless $dbl == 1;
        push @h, \@d;

        # Make the x,y cols:
        my @u = ();
        for (my $i=0; $i<@y; $i++) {
          push @u, [0.5*(2*$x2+$xbinsize), 0.5*(2*$y[$i]+$ybinsize)];
        }
        push @x, \@u;
      }
    }
    if ($diffnull) {
      # Make a histogram of the second column:
      !$normalise and die "You have to use --normalise with --diffnull.\n";

      @data = sort { $a->[1] <=> $b->[1] } @data;
      my $i = 0;
      my $n = 0;
      my $x2 = $firstybin;
      my @yh = ();
      while ($i < $N) {
        $x2 += $ybinsize;
        $x2 = sprintf("%.12f", $x2);
        $yh[$n] = 0;
        while ($i < $N && $data[$i][1] < $x2) {
          $yh[$n] = $yh[$n] + 1;
          ++$i;
        }
        $yh[$n] *= $scale;
        ++$n;
      }
      while ($n < $minybins + 1) {
        $y[$n] = $x2;
        $yh[$n] = 0;
        $x2 += $ybinsize;
        $x2 = sprintf("%.12f", $x2);
        $yh[$n] *= $scale;
        $n++;
      }

      @{$h[0]} == @yh && @h == @xh or die;

      if ($cumulative) {
        for (my $i=0; $i<@xh-1; $i++) {
          my $cum = 0;
          for (my $j=0; $j<@yh; $j++) {
            chomp $h[$i][$j];
            $cum += $xh[$i] * $yh[$j];
            $h[$i][$j] -= $cum;
            $h[$i][$j] .= "\n";
          }
        }
      } elsif ($reverse) {

        for (my $i=$#xh-1; $i>=0; $i--) {
          my $rev = 0;
          for (my $j=$#yh; $j>=0; $j--) {
            chomp $h[$i][$j];
            $rev += $xh[$i] * $yh[$j];
            $h[$i][$j] -= $rev;
            $h[$i][$j] .= "\n";
          }
        }
      } else {
        for (my $i=0; $i<@xh; $i++) {
          for (my $j=0; $j<@yh; $j++) {
            chomp $h[$n];
            $h[$i][$j] -= $xh[$i] * $yh[$j];
            $h[$i][$j] .= "\n";
          }
        }
      }
    }
  }
}

# Smoothing of plot:
if (@C == 1 && $smooth) {
  my $avrg = 0;
  my $diff = 0;
  my $prev_diff = 0;
  my $penalty = 0;
  if ($cumulative || $reverse) {
    my $step = 0;
    my $prev_step = 0;
    for (my $n = 0; $n < @h; $n++) {
      if ($n == 0) {
        $step = $h[$n];
      } else {
        $step = $h[$n] - $h[$n-1];
        $diff = $step - $prev_step;
        $diff /= $xbinsize; # To take into account that the heights
                            # and not the areas sum to one.
        if ($diff && $prev_diff and ($diff > 0 xor $prev_diff > 0)) {
          $penalty += abs($diff-$prev_diff)/2;
        }
      }
      $prev_step = $step;
      $prev_diff = $diff;
    }
  } else {
    for (my $n = 0; $n < @h; $n++) {
      if ($n == 0) {
        $diff = 0; # 0 and not $h[$n] because we don't what the first
                   # jump from 0 to count.
      } else {
        $diff = $h[$n] - $h[$n-1];
        if ($diff && $prev_diff and ($diff > 0 xor $prev_diff > 0)) {
          $penalty += abs($diff-$prev_diff)/2;
        }
      }
      $prev_diff = $diff;
    }
  }
  if ($penalty > $smooth) {
    @h = undef;
    @x = undef;
    $xbinsize += 1;
    goto REDO;
  }
  print STDERR "Smoothed to bin size: $xbinsize\n";
}

# Do the printing:
if (@C == 2) {
  if ($contour) {
    for (my $i=0; $i<@h-1; $i++) {
      my $j;
      for ($j=0; $j<@{$h[$i]}-1; $j++) {
        print $out "$x[$i][$j][0]\t$x[$i][$j][1]\t$h[$i][$j]\n";
        print $out "$x[$i][$j][0]\t$x[$i][$j+1][1]\t$h[$i][$j]\n";
      }
      print $out "$x[$i][$j][0]\t$x[$i][$j][1]\t$h[$i][$j]\n\n";

      for ($j=0; $j<@{$h[$i]}-1; $j++) {
        print $out "$x[$i+1][$j][0]\t$x[$i+1][$j][1]\t$h[$i][$j]\n";
        print $out "$x[$i+1][$j][0]\t$x[$i+1][$j+1][1]\t$h[$i][$j]\n";
      }
      print $out "$x[$i][$j][0]\t$x[$i][$j][1]\t$h[$i][$j]\n\n";
    }
  } else {
    for (my $i=0; $i<@h-1+$nulledge; $i++) {
      for (my $j=0; $j<@{$h[$i]}-1+$nulledge; $j++) {
        if ($centerbin) {
          print $out $x[$i][$j][0] + $xbinsize/2, "\t", $x[$i][$j][1] + $ybinsize/2, "\t$h[$i][$j]\n";
        } else {
          print $out $x[$i][$j][0], "\t", $x[$i][$j][1], "\t$h[$i][$j]\n";
        }
      }
      print $out "\n";
    }
  }
} elsif ($contour) {
  print $out "$x[0]\t0\n";
  my $n;
  for ($n = 0; $n < $#h; $n++) {
    print $out "$x[$n]\t$h[$n]\n";
    print $out "$x[$n+1]\t$h[$n]\n";
  }
  print $out "$x[$n]\t$h[$n]\n";
  print $out $x[$n]+$xbinsize,"\t$h[$n]\n";
  print $out $x[$n]+$xbinsize,"\t0\n";
} elsif ($float) {
  print $out "$x[0]\t0\n";
  my $n;
  for ($n = 0; $n < $#h; $n++) {
    print $out "$x[$n]\t$h[$n]\n";
    print $out "$x[$n+1]\t$h[$n]\n";
  }
  print $out "$x[$n]\t$h[$n]\n";
} else {
  if ($cdf) {
    for (my $n = 0; $n < @h+1; $n++) {
      if ($n == 0) {
        print $out "$x[$n]\t0\n";
      } elsif ($n == @h) {
        printf $out "%f\t$h[$n-1]\n", $x[$n-1]+($x[$n-1]-$x[$n-2]);
      } else {
        print $out "$x[$n]\t$h[$n-1]\n";
      }
    }
  } else {
    # Give x-value as center of bin:
    for (my $n = 0; $n < @h; $n++) {
      my $c;
      if ($centerbin) {
        $c = $x[$n] + 0.5 * $xbinsize;
      } else {
        $c = $x[$n];
      }
      print $out "$c\t$h[$n]\n";
    }
  }
}
close $out;

# Do quick and dirty plotting:
if ($plot || $save) {

  # Print gnuplot code to a tmpfile:
  open my $tmpfile, ">/tmp/tmp.gp" or die "$!\n";

  if ($logz) {
    print $tmpfile "set logscale z $logz\n";
  }
  if ($logy) {
    print $tmpfile "set logscale y $logy\n";
  }
  if ($logx) {
    print $tmpfile "set logscale x $logx\n";
  }

  if (@C == 1  and $contour || $float) {
    print $tmpfile "
set data style lines
set yrange [0:*]
plot '$output'
";
  } elsif (@C == 1 and $cdf) {
    print $tmpfile "
set data style points
set yrange [0:*]
plot '$output'
";
  } elsif (@C == 1) {
    print $tmpfile "
set data style boxes
set boxwidth $xbinsize
set yrange [0:*]
plot '$output'
";
  } elsif (@C == 2 && $contour) {
    print $tmpfile "
set style data lines
set hidden3d
splot '$output';
";
  } elsif (@C == 2 && $nulledge) {
    print $tmpfile "
set pm3d at s corners2color c
set style data pm3d
set view 0,0,1,1
set colorbox user origin .82,.27 size .02,.5
splot '$output';
";
  } else {
    print $tmpfile "
set pm3d at s corners2color c1
set data style pm3d
set colorbox user origin .82,.27 size .02,.5
splot '$output';
";
  }

  if ($save) {
    print $tmpfile "
save \"$save.gp\"
set output \"$save.eps\"
set term postscript eps color solid \"Helvetica\"
replot
";
  } else {
    print $tmpfile "
save '/tmp/plot.gp'
";

  }

  close $tmpfile;

  exec "gnuplot -persist /tmp/tmp.gp";
}

exit 0;

sub max {
  return $_[0] if @_ == 1;
  $_[0] > $_[1] ? $_[0] : $_[1]
}

sub min {
  return $_[0] if @_ == 1;
  $_[0] < $_[1] ? $_[0] : $_[1]
}

=head1 SYNOPSIS:

 histogram.pl [OPTIONS] [infile [outfile]]

=head1 DESCRIPTION:

Makes a 2D or 3D histogram data-set for gnuplot from data in specified
column(s) of an input file. Lines not starting with a real number are
ignored. It also understands "framed" tables dumped from databases.

=head1 OPTIONS:

=over 4

=item --help

Prints this help.

=item --[no]onlyreal

Ignore lines not starting with alpha chars. This is
default. By specifying --noonlyreal only lines starting
with '#' are ignored

=item --column <int>[,<int>]

Column number to use (starts at 1). Default is 1. If two
comma seperated numbers are given 3d histogram output is
printed (the format that splot in gnuplot takes.)

=item --binsize|--xbinsize <float>

Bin size. Bin size for the x-column in 3D histograms.

=item --plot

Invokes gnuplot and shows a quick and dirty plot. The
generated plot gets saved as tmp.gp.

=item --save <basename>

Same as --plot but saves a gnuplot file and a eps file
with the specified basename.

=item --logz <float>

Use with --plot to get log base <float> z-axis

=item --logy <float>

Use with --plot to get log base <float> y-axis

=item --logx <float>

Use with --plot to get log base <float> x-axis

=item --contour

Prints contour points at the borders of the bins to
produce a contour line in gnuplot.

=item --[no]centerbin

Whether the x value of 2D plots resed with 2D and 3D histograms to specify the lowest
x-value to be considered.

=item --lastx <float>

Used with 2D and 3D histograms to specify the highest
x-value to be considered. NOTE: The script will adjust
this value to match a bin border

=item --xrange [firstx]:[lastx]

Convenience option to specify first and last x-value specified.

=item --firsty <float>

Used with 3D histograms to make the center of the first y-bin at
least <float>.

=item --lasty <float>

Used with 3D histograms to make the center of the last y-bin at
least <float>.

=item --yrange [firstx]:[lastx]

Convenience option to specify first and last y-value specified.

=item --xbins <int>

Used with 2D or 3D histograms to make the the number of x-bins
at least <int> directions).

=item --ybins <int>

Used with 3D histograms to make the the number of y-bins
at least <int> directions).

=item --squarematrix

Used with 3D histograms to make the geneneated data
matrix squareshaped (same number of bins in both
directions).

=item --diffnull

Used with 3D histograms substract the nullmodel of
independent cols. That is to get P(A,B)-P(A)P(B).

=back

=head1 EXAMPLES:

 # Make a histogram of one column:
 histogram.pl -bin 10 -col 2 file.tbl 2d.hist

 # Two columns:
 cat file.tbl | histogram.pl -bin 100 -col 3,4 > 3d.hist

=head1 AUTHOR:

Anders Krogh / Kasper Munch

=head1 COPYRIGHT:

This program is under the GNU public licence.

=cut

